namespace CSharpReadAndFit
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.LabelInformation = new System.Windows.Forms.Label();
            this.TextFileName = new System.Windows.Forms.TextBox();
            this.ButtonSend = new System.Windows.Forms.Button();
            this.LabelResultFittedSphere = new System.Windows.Forms.Label();
            this.ResultFittedSphere = new System.Windows.Forms.Label();
            this.LabelResultAllSelectedSphere = new System.Windows.Forms.Label();
            this.ResultAllSelectedSphere = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // LabelInformation
            // 
            this.LabelInformation.BackColor = System.Drawing.SystemColors.Control;
            this.LabelInformation.Cursor = System.Windows.Forms.Cursors.Default;
            this.LabelInformation.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LabelInformation.ForeColor = System.Drawing.SystemColors.ControlText;
            this.LabelInformation.Location = new System.Drawing.Point(12, 4);
            this.LabelInformation.Name = "LabelInformation";
            this.LabelInformation.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.LabelInformation.Size = new System.Drawing.Size(300, 49);
            this.LabelInformation.TabIndex = 0;
            this.LabelInformation.Text = "Please enter the name of an ASCII point cloud file with points and normals in the" +
                " edit box below, then press the Send button or the Enter key.";
            // 
            // TextFileName
            // 
            this.TextFileName.AcceptsReturn = true;
            this.TextFileName.BackColor = System.Drawing.SystemColors.Window;
            this.TextFileName.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.TextFileName.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextFileName.ForeColor = System.Drawing.SystemColors.WindowText;
            this.TextFileName.Location = new System.Drawing.Point(15, 66);
            this.TextFileName.MaxLength = 0;
            this.TextFileName.Name = "TextFileName";
            this.TextFileName.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.TextFileName.Size = new System.Drawing.Size(297, 20);
            this.TextFileName.TabIndex = 1;
            // 
            // ButtonSend
            // 
            this.ButtonSend.BackColor = System.Drawing.SystemColors.Control;
            this.ButtonSend.Cursor = System.Windows.Forms.Cursors.Default;
            this.ButtonSend.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ButtonSend.ForeColor = System.Drawing.SystemColors.ControlText;
            this.ButtonSend.Location = new System.Drawing.Point(122, 102);
            this.ButtonSend.Name = "ButtonSend";
            this.ButtonSend.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.ButtonSend.Size = new System.Drawing.Size(81, 33);
            this.ButtonSend.TabIndex = 2;
            this.ButtonSend.Text = "Send";
            this.ButtonSend.UseVisualStyleBackColor = false;
            this.ButtonSend.Click += new System.EventHandler(this.ButtonSend_Click);
            //
            // LabelResultFittedSphere
            //
            this.LabelResultFittedSphere.BackColor = System.Drawing.SystemColors.Control;
            this.LabelResultFittedSphere.Cursor = System.Windows.Forms.Cursors.Default;
            this.LabelResultFittedSphere.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LabelResultFittedSphere.ForeColor = System.Drawing.SystemColors.ControlText;
            this.LabelResultFittedSphere.Location = new System.Drawing.Point(5, 152);
            this.LabelResultFittedSphere.Name = "LabelResultFittedSphere";
            this.LabelResultFittedSphere.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.LabelResultFittedSphere.Size = new System.Drawing.Size(300, 17);
            this.LabelResultFittedSphere.TabIndex = 3;
            this.LabelResultFittedSphere.Text = "Name of the fitted sphere:";
            // 
            // ResultFittedSphere
            // 
            this.ResultFittedSphere.BackColor = System.Drawing.Color.Transparent;
            this.ResultFittedSphere.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ResultFittedSphere.Cursor = System.Windows.Forms.Cursors.Default;
            this.ResultFittedSphere.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ResultFittedSphere.ForeColor = System.Drawing.SystemColors.ControlText;
            this.ResultFittedSphere.Location = new System.Drawing.Point(8, 173);
            this.ResultFittedSphere.Name = "ResultFittedSphere";
            this.ResultFittedSphere.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.ResultFittedSphere.Size = new System.Drawing.Size(304, 20);
            this.ResultFittedSphere.TabIndex = 4;
            this.ResultFittedSphere.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            //
            // LabelResultAllSelectedSphere
            //
            this.LabelResultAllSelectedSphere.BackColor = System.Drawing.SystemColors.Control;
            this.LabelResultAllSelectedSphere.Cursor = System.Windows.Forms.Cursors.Default;
            this.LabelResultAllSelectedSphere.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LabelResultAllSelectedSphere.ForeColor = System.Drawing.SystemColors.ControlText;
            this.LabelResultAllSelectedSphere.Location = new System.Drawing.Point(5, 206);
            this.LabelResultAllSelectedSphere.Name = "LabelResultAllSelectedSphere";
            this.LabelResultAllSelectedSphere.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.LabelResultAllSelectedSphere.Size = new System.Drawing.Size(300, 17);
            this.LabelResultAllSelectedSphere.TabIndex = 5;
            this.LabelResultAllSelectedSphere.Text = "Name of all spheres:";
            //
            // ResultAllSelectedSphere
            //
            this.ResultAllSelectedSphere.BackColor = System.Drawing.Color.Transparent;
            this.ResultAllSelectedSphere.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ResultAllSelectedSphere.Cursor = System.Windows.Forms.Cursors.Default;
            this.ResultAllSelectedSphere.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ResultAllSelectedSphere.ForeColor = System.Drawing.SystemColors.ControlText;
            this.ResultAllSelectedSphere.Location = new System.Drawing.Point(8, 223);
            this.ResultAllSelectedSphere.Name = "ResultAllSelectedSphere";
            this.ResultAllSelectedSphere.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.ResultAllSelectedSphere.Size = new System.Drawing.Size(304, 20);
            this.ResultAllSelectedSphere.TabIndex = 6;
            this.ResultAllSelectedSphere.TextAlign = System.Drawing.ContentAlignment.TopCenter;

            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(324, 247);
            this.Controls.Add(this.LabelInformation);
            this.Controls.Add(this.TextFileName);
            this.Controls.Add(this.ButtonSend);
            this.Controls.Add(this.LabelResultFittedSphere);
            this.Controls.Add(this.ResultFittedSphere);
            this.Controls.Add(this.LabelResultAllSelectedSphere);
            this.Controls.Add(this.ResultAllSelectedSphere);

            this.Name = "MainForm";
            this.Text = "ASCII Point Cloud Read & Fit Sample";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.Label LabelInformation;
        public System.Windows.Forms.TextBox TextFileName;
        public System.Windows.Forms.Button ButtonSend;
        public System.Windows.Forms.Label LabelResultFittedSphere;
        public System.Windows.Forms.Label ResultFittedSphere;
        public System.Windows.Forms.Label LabelResultAllSelectedSphere;
        public System.Windows.Forms.Label ResultAllSelectedSphere;
    }
}

