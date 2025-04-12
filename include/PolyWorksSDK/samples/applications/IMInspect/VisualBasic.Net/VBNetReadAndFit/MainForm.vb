Public Class MainForm

    ' Global COM Message Filter to prevent COM calls from being rejected if the server application is temporarily busy
    Private comFilter As CComMessageFilter = Nothing

    ' Global access to a PolyWorks|Inspector
    Private imInspectObject As IMInspectLib.IMInspect = Nothing

    ' Upon loading the Form
    Private Sub MainForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        comFilter = New CComMessageFilter

        imInspectObject = New IMInspectLib.IMInspect

    End Sub

    ' Cleanup upon destruction of the form
    Private Sub MainForm_FormClosed(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles MyBase.FormClosed

        System.Runtime.InteropServices.Marshal.ReleaseComObject(imInspectObject)
        imInspectObject = Nothing

        comFilter = Nothing

    End Sub

    ' Main action of this application
    Private Sub ButtonSend_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonSend.Click

        ResultFittedSphere.Text = ""
        ResultAllSelectedSphere.Text = ""
        LabelResultAllSelectedSphere.Text = "Name of all spheres:"

        ' If the server does not exists, return
        If imInspectObject Is Nothing Then

            Exit Sub

        End If

        ' Obtain PolyWorks|Inspector's current project
        Dim projectObject As IMInspectLib.IIMInspectProject = Nothing
        imInspectObject.ProjectGetCurrent(projectObject)

        If projectObject Is Nothing Then

            Exit Sub

        End If

        ' Read the file and fill the coordinates and normals lists
        Dim coordinates As System.Collections.Generic.List(Of Single) = New System.Collections.Generic.List(Of Single)()
        Dim normals As System.Collections.Generic.List(Of Single) = New System.Collections.Generic.List(Of Single)()
        Dim colors As System.Collections.Generic.List(Of Byte) = New System.Collections.Generic.List(Of Byte)()

        If FillArraysFromFile((TextFileName.Text), coordinates, normals) = False Then

            Exit Sub

        End If


        ' Set all points to a blue color
        Dim index As Integer
        index = 0

        While index < coordinates.Count

            colors.Add(32)
            colors.Add(32)
            colors.Add(224)
            index += 3

        End While

        ' Obtain the name of the file, without the path
        Dim tokens As String() = TextFileName.Text.Split(New [Char]() {"\"c})
        Dim objectName As String = tokens(tokens.Length - 1)

        ' Create a point cloud in the current PolyWorks|Inspector project
        Dim pointCloudObject As IMInspectLib.IIMPointCloud
        projectObject.PointCloudCreateData(pointCloudObject, objectName, 0)

        ' Send the points to the point cloud
        If Not pointCloudObject Is Nothing Then

            pointCloudObject.PointsAdd(coordinates.ToArray(), normals.ToArray(), colors.ToArray())

        End If

        ' Obtain a Command Center from the current PolyWorks|Inspector project
        Dim commandCenterObject As IMInspectLib.IIMCommandCenter
        projectObject.CommandCenterCreate(commandCenterObject)

        ' Send commands to fit a sphere on all the elements of this new object
        Dim returnValue As Integer
        Dim script As String
        Dim sphereName As String

        If Not commandCenterObject Is Nothing Then

            commandCenterObject.CommandExecute("TREEVIEW OBJECT SELECT NONE")

            ' Perform the fit
            commandCenterObject.CommandExecute("TREEVIEW OBJECT_ELEMENTS SELECT ALL ( """ & objectName & """ )")
            commandCenterObject.CommandExecute("FEATURE PRIMITIVE SPHERE FIT_FROM_SELECTED_ELEMENTS")
            If commandCenterObject.ReturnValueIsSuccess(returnValue) = 0 Then

                ResultFittedSphere.Text = "The fitting was unsuccessful"
                Exit Sub

            End If

            ' Gets the name of the last fitted sphere. After the fitting, it is the only object selected.
            Dim lastSphereName As String
            If Not ValueStrGetFromApp(commandCenterObject, "TREEVIEW OBJECT PROPERTIES NAME GET", lastSphereName, False, "") Then

                ResultFittedSphere.Text = "Unable to obtain the name of the fitted sphere"
            Else
                ' Feedback of the name of the last fitted sphere
                ResultFittedSphere.Text = "Sphere """ & lastSphereName & """ was successfully fitted"
            End If

            ' Gets the name of all spheres
            commandCenterObject.CommandExecute("TREEVIEW OBJECT SELECT NONE")
            commandCenterObject.CommandExecute("TREEVIEW PRIMITIVE SPHERE SELECT ALL")

            Dim sphereNames As System.Collections.Generic.List(Of System.Collections.Generic.List(Of String)) = New System.Collections.Generic.List(Of System.Collections.Generic.List(Of String))
            Dim res As Boolean = ValueStrArrayGetFromApp(commandCenterObject, "TREEVIEW OBJECT NAME SELECTED GET", sphereNames, False, "")

            ' Feedback of the name of all spheres
            If (res And (Not (sphereNames.Count = 0))) Then
                NameSpheresFeedback(sphereNames(0), LabelResultAllSelectedSphere, ResultAllSelectedSphere)
            Else
                ResultAllSelectedSphere.Text = "Unable to obtain the name of the selected objects"
            End If

        End If

        ' Cleanup
        System.Runtime.InteropServices.Marshal.ReleaseComObject(pointCloudObject)
        System.Runtime.InteropServices.Marshal.ReleaseComObject(commandCenterObject)
        System.Runtime.InteropServices.Marshal.ReleaseComObject(projectObject)

        pointCloudObject = Nothing
        commandCenterObject = Nothing
        projectObject = Nothing

    End Sub

    '=================================================================================================
    ' Indicates if the specified list of strings Is empty.
    '
    ' Parameter : sphereNames_ : sphere names
    '
    ' Return : true if empty, false otherwise
    '=================================================================================================
    Private Function IsSphereNamesEmpty(ByRef sphereNames_ As System.Collections.Generic.List(Of String)) As Boolean

        If (sphereNames_.Count = 0) Then Return True

        ' Note that in MSCL, an empty array has a size of 1 And that the corresponding element Is always 0 whatever its type (int, float, string...).
        If (sphereNames_.Count = 1) Then
            If (sphereNames_(0) = "0") Then
                Return True
            End If
        End If

        Return False
    End Function

    '=================================================================================================
    ' Feedback of the name of all spheres
    '
    ' Parameter : sphereNames_                  : spher names
    ' Parameter : labelResultAllSelectedSphere_ : (out) label result to feedback
    ' Parameter : resultAllSelectedSphere_      : (out) result to feedback
    '=================================================================================================
    Private Function NameSpheresFeedback(ByRef sphereNames_ As System.Collections.Generic.List(Of String),
                                         ByRef labelResultAllSelectedSphere_ As Label,
                                         ByRef resultAllSelectedSphere_ As Label)

        Dim suffix As String = "sphere"

        Dim nbSpheres As Integer = sphereNames_.Count
        If nbSpheres = 1 Then
            If sphereNames_(0).Equals("0") Then
                nbSpheres = 0
            End If
        End If

        If nbSpheres > 1 Then
            suffix = "spheres"
        End If

        labelResultAllSelectedSphere_.Text = "Name of all spheres: ( " & nbSpheres & " " & suffix & " )"

        For i As Integer = 0 To nbSpheres - 1
            If i > 0 Then
                resultAllSelectedSphere_.Text += ", "
            End If
            resultAllSelectedSphere_.Text += sphereNames_(i)
        Next
    End Function

    '=================================================================================================
    '   Retrieves a string value from the application, using a command.
    '
    ' Parameter : commandCenter_ : command center
    ' Parameter : cmdName_       : command name
    ' Parameter : value_         : (out) retrieved value
    ' Parameter : withEcho_      : indicates whether the command should be visible in the application's Command History
    ' Parameter : cmdArg_        : command arguments
    '
    ' Return : true if successful, false otherwise
    ' -------------------------------------------------------------------------------------------------
    Private Function ValueStrGetFromApp(
        ByRef commandCenter_ As IMInspectLib.IIMCommandCenter,
        ByRef cmdName_ As String,
        ByRef value_ As String,
        ByRef withEcho_ As Boolean,
        ByRef cmdArg_ As String) As Boolean

        Dim values As System.Collections.Generic.List(Of System.Collections.Generic.List(Of String)) = New System.Collections.Generic.List(Of System.Collections.Generic.List(Of String))

        If Not ValueStrArrayGetFromApp(commandCenter_, cmdName_, values, withEcho_, cmdArg_) Then
            Return False
        End If

        If ((values.Count = 0) OrElse
            (values(0).Count = 0)) Then
            Return False
        End If

        value_ = values(0)(0)

        Return True

    End Function

    '=================================================================================================
    '   Retrieves an array of string values from the application, using a command.
    '
    ' Parameter : commandCenter_ : command center
    ' Parameter : cmdName_       : command name
    ' Parameter : values_        : (out) retrieved values
    ' Parameter : withEcho_      : indicates whether the command should be visible in the application's Command History
    ' Parameter : cmdArg_        : command arguments
    '
    ' Return : true if successful, false otherwise
    ' -------------------------------------------------------------------------------------------------
    Private Function ValueStrArrayGetFromApp(
        ByRef commandCenter_ As IMInspectLib.IIMCommandCenter,
        ByRef cmdName_ As String,
        ByRef values_ As System.Collections.Generic.List(Of System.Collections.Generic.List(Of String)),
        ByRef withEcho_ As Boolean,
        ByRef cmdArg_ As String) As Boolean

        Dim valueVar As String = "value"
        Dim script As String = "version ""5.0""" & vbCrLf &
                               "DECLARE " & valueVar & vbCrLf &
                                cmdName_ & " ( "
        If (Not String.IsNullOrEmpty(cmdArg_)) Then
            script += """" + cmdArg_ + """, "
        End If
        script += valueVar & " )"

        Dim values As System.Collections.Generic.List(Of String) = New System.Collections.Generic.List(Of String)()

        Dim valueVarArray As System.Collections.Generic.List(Of String) = New System.Collections.Generic.List(Of String)()
        valueVarArray.Add(valueVar)

        If Not RunScriptAndReadValueArrays(commandCenter_, script, valueVarArray, values_, withEcho_) Then
            Return False
        End If

        Return True

    End Function

    '=================================================================================================
    '   Retrieves the values of each variable when running a given script
    '
    ' Parameter : commandCenter_ : command center
    ' Parameter : script_        : script to execute
    ' Parameter : varNames_      : name of the variables to retrieve
    ' Parameter : values_        : retrieved values of each variable
    ' Parameter : withEcho_      : indicates whether the command should be visible in the application's Command History
    '
    ' Return : true if successful, false otherwise
    ' -------------------------------------------------------------------------------------------------
    Private Function RunScriptAndReadValueArrays(
        ByRef commandCenter_ As IMInspectLib.IIMCommandCenter,
        ByRef script_ As String,
        ByRef varNames_ As System.Collections.Generic.List(Of String),
        ByRef values_ As System.Collections.Generic.List(Of System.Collections.Generic.List(Of String)),
        ByRef withEcho_ As Boolean) As Boolean

        If (withEcho_ = True) Then
            commandCenter_.CommandExecute("EchoOn")
            commandCenter_.CommandExecute("RecordableOn")
        Else
            commandCenter_.CommandExecute("EchoOff")
            commandCenter_.CommandExecute("RecordableOff")
        End If

        ' Run the script
        Dim returnValue = commandCenter_.ScriptExecuteFromBuffer(script_, "")
        If commandCenter_.ReturnValueIsSuccess(returnValue) = 0 Then
            Return False
        End If

        ' Retrieves the values of each variable
        For i As Integer = 0 To varNames_.Count - 1

            Dim nbValues As String
            Dim values As System.Collections.Generic.List(Of String) = New System.Collections.Generic.List(Of String)

            nbValues = commandCenter_.ScriptVariableGetNbValues(varNames_(i))

            For j As Integer = 0 To nbValues - 1

                Dim value As String
                returnValue = commandCenter_.ScriptVariableGetValueAsString(varNames_(i), j + 1, value)

                If commandCenter_.ReturnValueIsSuccess(returnValue) = 1 Then
                    values.Add(value)
                End If
            Next
            values_.Add(values)

        Next

        Return True

    End Function

    '=================================================================================================
    ' Reads an ASCII file containing lines made of 6 values (X,Y,Z,I,J,K)
    ' and fills a coordinates and a normals arrays with those values
    '=================================================================================================
    Private Function FillArraysFromFile(
        ByRef filename_ As String,
        ByRef coordinates_ As System.Collections.Generic.List(Of Single),
        ByRef normals_ As System.Collections.Generic.List(Of Single)) As Boolean

        ' Validate file name
        If Not System.IO.File.Exists(filename_) Then

            Return False

        End If

        ' Open the file for reading
        Dim reader As New System.IO.StreamReader(filename_)
        Dim line As String
        Dim success As Boolean

        ' Read the first six tokens (X,Y,Z,I,J,K) on each line of the file
        ' and convert them to double-precision floating point values
        success = True
        line = reader.ReadLine()

        While Not line Is Nothing

            Dim tokens As String() = line.Split(New [Char]() {" "c})

            If tokens.Length < 6 Then

                success = False
                Exit While

            End If

            ' Recording coordinates
            coordinates_.Add(Convert.ToSingle(tokens(0)))
            coordinates_.Add(Convert.ToSingle(tokens(1)))
            coordinates_.Add(Convert.ToSingle(tokens(2)))

            ' Recording normals
            normals_.Add(Convert.ToSingle(tokens(3)))
            normals_.Add(Convert.ToSingle(tokens(4)))
            normals_.Add(Convert.ToSingle(tokens(5)))

            line = reader.ReadLine()

        End While

        reader.Close()

        Return success

    End Function

End Class
