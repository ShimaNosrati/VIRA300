using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace CSharpReadAndFit
{
    public partial class MainForm : Form
    {
        // =========================================================================================
        // ========================================= Members =======================================

        private IMInspectLib.IMInspect m_imInspect = null;

        // =========================================================================================
        // ========================================= Methods =======================================

        // =========================================================================================
        // Constructor
        // -----------------------------------------------------------------------------------------
        public MainForm()
        {
            InitializeComponent();
        }

        // =========================================================================================
        // Upon loading the form
        // -----------------------------------------------------------------------------------------
        private void MainForm_Load(object sender, EventArgs e)
        {
            m_imInspect = new IMInspectLib.IMInspect();
        }

        // =========================================================================================
        // Cleanup upon destruction of the form
        // -----------------------------------------------------------------------------------------
        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            System.Runtime.InteropServices.Marshal.ReleaseComObject(m_imInspect);
            m_imInspect = null;
        }

        // =========================================================================================
        // Main action of this application
        // -----------------------------------------------------------------------------------------
        private void ButtonSend_Click(object sender, EventArgs e)
        {
            ResultFittedSphere.Text = "";
            ResultAllSelectedSphere.Text = "";
            LabelResultAllSelectedSphere.Text = "Name of all spheres:";

            // If the server does not exists, return
            if (m_imInspect == null)
            {
                return;
            }

            // Obtain PolyWorks|Inspector's current project
            IMInspectLib.IIMInspectProject inspectProject = null;
            m_imInspect.ProjectGetCurrent(out inspectProject);

            if (inspectProject == null)
            {
                return;
            }

            // Read the file and fill the coordinates and normals lists
            System.Collections.Generic.List<float> coordinates = new System.Collections.Generic.List<float>();
            System.Collections.Generic.List<float> normals = new System.Collections.Generic.List<float>();
            System.Collections.Generic.List<Byte> colors = new System.Collections.Generic.List<Byte>();

            if (!FillArraysFromFile(TextFileName.Text, ref coordinates, ref normals))
            {
                return;
            }

            // Set all points to a blue color
            for (int index = 0; index < coordinates.Count; index += 3)
            {
                colors.Add(32);
                colors.Add(32);
                colors.Add(224);
            }

            // Obtain the name of the file, without the path
            string[] tokens = TextFileName.Text.Split(new Char[] { '\\' });
            string objectName = tokens[tokens.Length - 1];

            // Create a point cloud in the current PolyWorks|Inspector project
            IMInspectLib.IIMPointCloud pointCloud = null;
            inspectProject.PointCloudCreateData(out pointCloud, objectName, 0);

            // Send the points to the point cloud
            if (pointCloud != null)
            {
                Array coordinatesArray = coordinates.ToArray();
                Array normalsArray = normals.ToArray();
                Array colorsArray = colors.ToArray();

                pointCloud.PointsAdd(ref coordinatesArray, ref normalsArray, ref colorsArray);
            }

            // Obtain a Command Center from the current PolyWorks|Inspector project
            IMInspectLib.IIMCommandCenter commandCenter = null;
            inspectProject.CommandCenterCreate(out commandCenter);

            // Send commands to fit a sphere on all the elements of this new object
            int returnValue = 0;

            if (commandCenter != null)
            {
                commandCenter.CommandExecute("TREEVIEW OBJECT SELECT NONE");

                // Perform the fit
                commandCenter.CommandExecute("TREEVIEW OBJECT_ELEMENTS SELECT ALL ( \"" + objectName + "\" )");
                returnValue = commandCenter.CommandExecute("FEATURE PRIMITIVE SPHERE FIT_FROM_SELECTED_ELEMENTS");
                if (commandCenter.ReturnValueIsSuccess(returnValue) == 0)
                {
                    ResultFittedSphere.Text = "The fitting was unsuccessful";
                }

                // Gets the name of the last fitted sphere. After the fitting, it is the only object selected.
                String lastSphereName = "";
                if (!ValueStrGetFromApp(commandCenter, "TREEVIEW OBJECT PROPERTIES NAME GET", ref lastSphereName, false, ""))
                {
                    ResultFittedSphere.Text = "Unable to obtain the name of the fitted sphere";
                }
                else
                {
                    // Feedback of the name of the last fitted sphere
                    ResultFittedSphere.Text = "Sphere " + lastSphereName + " was successfully fitted";
                }

                // Gets the name of all spheres
                commandCenter.CommandExecute("TREEVIEW OBJECT SELECT NONE");
                commandCenter.CommandExecute("TREEVIEW PRIMITIVE SPHERE SELECT ALL");

                System.Collections.Generic.List<System.Collections.Generic.List<String>> sphereNames = new System.Collections.Generic.List<System.Collections.Generic.List<String>>();
                bool res = ValueStrArrayGetFromApp(commandCenter, "TREEVIEW OBJECT NAME SELECTED GET", ref sphereNames, false, "");

                // Feedback of the name of all spheres
                if (res && (sphereNames.Count != 0))
                {
                    NameSpheresFeedback(sphereNames[0], ref LabelResultAllSelectedSphere, ref ResultAllSelectedSphere);
                }
                else
                {
                    ResultAllSelectedSphere.Text = "Unable to obtain the name of the selected objects";
                }
            }

            // Cleanup
            System.Runtime.InteropServices.Marshal.ReleaseComObject(pointCloud);
            pointCloud = null;
            System.Runtime.InteropServices.Marshal.ReleaseComObject(commandCenter);
            commandCenter = null;
            System.Runtime.InteropServices.Marshal.ReleaseComObject(inspectProject);
            inspectProject = null;
        }

        // =========================================================================================
        // ======================================== Utilities ======================================

        //=================================================================================================
        // Indicates if the specified list of strings is empty.
        //
        // Parameter : sphereNames_ : sphere names
        //
        // Return : true if empty, false otherwise
        //=================================================================================================
        private bool IsSphereNamesEmpty(System.Collections.Generic.List<String> sphereNames_)
        {
            if (sphereNames_.Count == 0) return true;

            // Note that in MSCL, an empty array has a size of 1 and that the corresponding element is always 0 whatever its type (int, float, string...).
            if (sphereNames_.Count == 1)
            {
                if (sphereNames_[0].Equals("0"))
                    return true;
            }

            return false;
        }

        //=================================================================================================
        // Feedback of the name of all spheres
        //
        // Parameter : sphereNames_                  : sphere names
        // Parameter : labelResultAllSelectedSphere_ : (out) label result to feedback
        // Parameter : resultAllSelectedSphere_      : (out) result to feedback
        //=================================================================================================
        private void NameSpheresFeedback(System.Collections.Generic.List<String> sphereNames_,
                                         ref Label labelResultAllSelectedSphere_,
                                         ref Label resultAllSelectedSphere_)
        {
            String suffix = "sphere";
            int nbSpheres = 0;

            if ( !IsSphereNamesEmpty(sphereNames_) )
            {
                nbSpheres = sphereNames_.Count;
                if (nbSpheres > 1) suffix = "spheres";
            }

            labelResultAllSelectedSphere_.Text = "Name of all spheres: ( " + nbSpheres + " " + suffix + " )";

            for( int i = 0; i < nbSpheres; i++ )
            {
                if (i > 0) resultAllSelectedSphere_.Text += ", ";

                resultAllSelectedSphere_.Text += sphereNames_[i];
            }
        }

        // =========================================================================================
        // Reads an ASCII file containing lines made of 6 values (X,Y,Z,I,J,K)
        // and fills a coordinates and a normals lists with those values
        // -----------------------------------------------------------------------------------------
        private bool FillArraysFromFile(
            String filename_,
            ref System.Collections.Generic.List<float> coordinates_,
            ref System.Collections.Generic.List<float> normals_)
        {
            // Validate file name
            if ( !File.Exists( filename_ ) )
            {
                return false;
            }

            // Open the file for reading
            StreamReader reader = new StreamReader( filename_ );
            String line;
            bool success = true;

            // Read the first six tokens (X,Y,Z,I,J,K) on each line of the file
            // and convert them to double-precision floating point values
            while ( ( line = reader.ReadLine() ) != null )
            {
                string[] tokens = line.Split( new Char[] { ' ' } );

                if ( tokens.Length < 6 )
                {
                    success = false;

                    break;
                }

                // Recording coordinates
                coordinates_.Add( Convert.ToSingle( tokens[ 0 ] ) );
                coordinates_.Add( Convert.ToSingle( tokens[ 1 ] ) );
                coordinates_.Add( Convert.ToSingle( tokens[ 2 ] ) );

                // Recording normals
                normals_.Add( Convert.ToSingle( tokens[ 3 ] ) );
                normals_.Add( Convert.ToSingle( tokens[ 4 ] ) );
                normals_.Add( Convert.ToSingle( tokens[ 5 ] ) );
            }

            reader.Close();

            return success;
        }

        //=================================================================================================
        //   Retrieves a string value from the application, using a command.
        //
        // Parameter : commandCenter_ : command center
        // Parameter : cmdName_       : command name
        // Parameter : value_         : (out) retrieved value
        // Parameter : withEcho_      : indicates whether the command should be visible in the application's Command History
        // Parameter : cmdArg_        : command arguments
        //
        // Return : true if successful, false otherwise
        // -------------------------------------------------------------------------------------------------
        private bool ValueStrGetFromApp(
            IMInspectLib.IIMCommandCenter commandCenter_,
            String cmdName_,
            ref String value_,
            bool withEcho_,
            String cmdArg_)
        {
            value_ = "";
            System.Collections.Generic.List<System.Collections.Generic.List<String>> values = new System.Collections.Generic.List<System.Collections.Generic.List<String>>();

            if (!ValueStrArrayGetFromApp(commandCenter_, cmdName_, ref values, withEcho_, cmdArg_))
            {
                return false;
            }

            if( (values.Count == 0) || (values[0].Count == 0) )
            {
                return false;
            }

            value_ = values[0][0];
            return true;
        }

        // =================================================================================================
        //    Retrieves an array of string values from the application, using a command.
        //
        //  Parameter : commandCenter_ : command center
        //  Parameter : cmdName_       : command name
        //  Parameter : values_        : (out) retrieved values
        //  Parameter : withEcho_      : indicates whether the command should be visible in the application's Command History
        //  Parameter : cmdArg_        : command arguments
        //
        //  Return : true if successful, false otherwise
        //  -------------------------------------------------------------------------------------------------
        private bool ValueStrArrayGetFromApp(
            IMInspectLib.IIMCommandCenter commandCenter_,
            String cmdName_,
            ref System.Collections.Generic.List<System.Collections.Generic.List<String>> values_,
            bool withEcho_,
            String cmdArg_)
        {
            String valueVar = "value";
            String script = "version \"5.0\"" + System.Environment.NewLine;
            script += "DECLARE " + valueVar + System.Environment.NewLine;
            script += cmdName_ + " ( ";
            if (!String.IsNullOrEmpty(cmdArg_))
            {
                script += "\"" + cmdArg_ + "\", ";
            }
            script += valueVar + " )";

            System.Collections.Generic.List<String> values = new System.Collections.Generic.List<String>();
            System.Collections.Generic.List<String> valueVarArray = new System.Collections.Generic.List<String>();
            valueVarArray.Add(valueVar);
            if ( ! RunScriptAndReadValueArrays(commandCenter_, script, valueVarArray, ref values_, withEcho_) )
            {
                return false;
            }

            return true;
        }

        //=================================================================================================
        //   Retrieves the values of each variable when running a given script
        //
        // Parameter : commandCenter_ : command center
        // Parameter : script_        : script to execute
        // Parameter : varNames_      : name of the variables to retrieve
        // Parameter : values_        : retrieved values of each variable
        // Parameter : withEcho_      : indicates whether the command should be visible in the application's Command History
        //
        // Return : true if successful, false otherwise
        // -------------------------------------------------------------------------------------------------
        private bool RunScriptAndReadValueArrays(
            IMInspectLib.IIMCommandCenter commandCenter_,
            String script_,
            System.Collections.Generic.List<String> varNames_,
            ref System.Collections.Generic.List<System.Collections.Generic.List<String>> values_,
            bool withEcho_)
        {
            if( withEcho_)
            {
                commandCenter_.CommandExecute("EchoOn");
                commandCenter_.CommandExecute("RecordableOn");
            }
            else
            {
                commandCenter_.CommandExecute("EchoOff");
                commandCenter_.CommandExecute("RecordableOff");

            }

            // Run the script
            int returnValue = commandCenter_.ScriptExecuteFromBuffer(script_, "");
            if (commandCenter_.ReturnValueIsSuccess(returnValue) == 0) return false;

            // Retrieves the values of each variable
            for ( int i = 0; i < varNames_.Count ; i++)
            {
                int nbValues;
                System.Collections.Generic.List<String> values = new System.Collections.Generic.List<String>();

                nbValues = commandCenter_.ScriptVariableGetNbValues(varNames_[i]);

                for( int j = 0; j < nbValues; j++)
                {
                    String value;
                    returnValue = commandCenter_.ScriptVariableGetValueAsString(varNames_[i], j+1, out value);
                    if (commandCenter_.ReturnValueIsSuccess(returnValue) == 1)
                    {
                        values.Add(value);
                    }
                }
                values_.Add(values);
            }
            return true;
        }
    }
}