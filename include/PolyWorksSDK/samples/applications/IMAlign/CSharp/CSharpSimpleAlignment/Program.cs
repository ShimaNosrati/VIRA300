using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace CSharpSimpleAlignment
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // Create a COM Message Filter to prevent COM calls from being rejected if the server application is temporarily busy
            using (var comMessageFilter = IM.CComMessageFilter.Create())
            {
                System.Diagnostics.Debug.Assert(comMessageFilter != null);
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new MainForm());
            }
        }
    }
}