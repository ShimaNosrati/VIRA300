<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class MainForm
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.LabelInformation = New System.Windows.Forms.Label
        Me.ButtonSend = New System.Windows.Forms.Button
        Me.TextFileName = New System.Windows.Forms.TextBox
        Me.LabelResultAllSelectedSphere = New System.Windows.Forms.Label
        Me.ResultFittedSphere = New System.Windows.Forms.Label
        Me.LabelResultFittedSphere = New System.Windows.Forms.Label
        Me.ResultAllSelectedSphere = New System.Windows.Forms.Label
        Me.SuspendLayout()
        '
        'LabelInformation
        '
        Me.LabelInformation.BackColor = System.Drawing.SystemColors.Control
        Me.LabelInformation.Cursor = System.Windows.Forms.Cursors.Default
        Me.LabelInformation.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.LabelInformation.ForeColor = System.Drawing.SystemColors.ControlText
        Me.LabelInformation.Location = New System.Drawing.Point(12, 9)
        Me.LabelInformation.Name = "LabelInformation"
        Me.LabelInformation.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.LabelInformation.Size = New System.Drawing.Size(300, 49)
        Me.LabelInformation.TabIndex = 3
        Me.LabelInformation.Text = "Please enter the name of an ASCII point cloud file with points and normals in the" & _
            " edit box below, then press the Send button or the Enter key."
        '
        'ButtonSend
        '
        Me.ButtonSend.BackColor = System.Drawing.SystemColors.Control
        Me.ButtonSend.Cursor = System.Windows.Forms.Cursors.Default
        Me.ButtonSend.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ButtonSend.ForeColor = System.Drawing.SystemColors.ControlText
        Me.ButtonSend.Location = New System.Drawing.Point(122, 102)
        Me.ButtonSend.Name = "ButtonSend"
        Me.ButtonSend.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.ButtonSend.Size = New System.Drawing.Size(81, 33)
        Me.ButtonSend.TabIndex = 5
        Me.ButtonSend.Text = "Send"
        Me.ButtonSend.UseVisualStyleBackColor = False
        '
        'TextFileName
        '
        Me.TextFileName.AcceptsReturn = True
        Me.TextFileName.BackColor = System.Drawing.SystemColors.Window
        Me.TextFileName.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.TextFileName.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TextFileName.ForeColor = System.Drawing.SystemColors.WindowText
        Me.TextFileName.Location = New System.Drawing.Point(15, 71)
        Me.TextFileName.MaxLength = 0
        Me.TextFileName.Name = "TextFileName"
        Me.TextFileName.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TextFileName.Size = New System.Drawing.Size(297, 20)
        Me.TextFileName.TabIndex = 4
        '
        'LabelResultFittedSphere
        '
        Me.LabelResultFittedSphere.BackColor = System.Drawing.SystemColors.Control
        Me.LabelResultFittedSphere.Cursor = System.Windows.Forms.Cursors.Default
        Me.LabelResultFittedSphere.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.LabelResultFittedSphere.ForeColor = System.Drawing.SystemColors.ControlText
        Me.LabelResultFittedSphere.Location = New System.Drawing.Point(5, 152)
        Me.LabelResultFittedSphere.Name = "LabelResultFittedSphere"
        Me.LabelResultFittedSphere.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.LabelResultFittedSphere.Size = New System.Drawing.Size(300, 17)
        Me.LabelResultFittedSphere.TabIndex = 9
        Me.LabelResultFittedSphere.Text = "Name of the fitted sphere:"
        '
        'ResultFittedSphere
        '
        Me.ResultFittedSphere.BackColor = System.Drawing.Color.Transparent
        Me.ResultFittedSphere.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.ResultFittedSphere.Cursor = System.Windows.Forms.Cursors.Default
        Me.ResultFittedSphere.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ResultFittedSphere.ForeColor = System.Drawing.SystemColors.ControlText
        Me.ResultFittedSphere.Location = New System.Drawing.Point(8, 173)
        Me.ResultFittedSphere.Name = "ResultFittedSphere"
        Me.ResultFittedSphere.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.ResultFittedSphere.Size = New System.Drawing.Size(304, 20)
        Me.ResultFittedSphere.TabIndex = 6
        Me.ResultFittedSphere.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'LabelResultAllSelectedSphere
        '
        Me.LabelResultAllSelectedSphere.BackColor = System.Drawing.SystemColors.Control
        Me.LabelResultAllSelectedSphere.Cursor = System.Windows.Forms.Cursors.Default
        Me.LabelResultAllSelectedSphere.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.LabelResultAllSelectedSphere.ForeColor = System.Drawing.SystemColors.ControlText
        Me.LabelResultAllSelectedSphere.Location = New System.Drawing.Point(5, 206)
        Me.LabelResultAllSelectedSphere.Name = "LabelResultAllSelectedSphere"
        Me.LabelResultAllSelectedSphere.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.LabelResultAllSelectedSphere.Size = New System.Drawing.Size(300, 17)
        Me.LabelResultAllSelectedSphere.TabIndex = 8
        Me.LabelResultAllSelectedSphere.Text = "Name of all spheres:"
        '
        'ResultAllSelectedSphere
        '
        Me.ResultAllSelectedSphere.BackColor = System.Drawing.Color.Transparent
        Me.ResultAllSelectedSphere.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.ResultAllSelectedSphere.Cursor = System.Windows.Forms.Cursors.Default
        Me.ResultAllSelectedSphere.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ResultAllSelectedSphere.ForeColor = System.Drawing.SystemColors.ControlText
        Me.ResultAllSelectedSphere.Location = New System.Drawing.Point(8, 223)
        Me.ResultAllSelectedSphere.Name = "ResultAllSelectedSphere"
        Me.ResultAllSelectedSphere.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.ResultAllSelectedSphere.Size = New System.Drawing.Size(304, 20)
        Me.ResultAllSelectedSphere.TabIndex = 7
        Me.ResultAllSelectedSphere.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'MainForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(324, 247)
        Me.Controls.Add(Me.LabelInformation)
        Me.Controls.Add(Me.TextFileName)
        Me.Controls.Add(Me.ButtonSend)
        Me.Controls.Add(Me.LabelResultFittedSphere)
        Me.Controls.Add(Me.ResultFittedSphere)
        Me.Controls.Add(Me.LabelResultAllSelectedSphere)
        Me.Controls.Add(Me.ResultAllSelectedSphere)
        Me.Name = "MainForm"
        Me.Text = "ASCII Point Cloud Read & Fit Sample"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Public WithEvents LabelInformation As System.Windows.Forms.Label
    Public WithEvents ButtonSend As System.Windows.Forms.Button
    Public WithEvents TextFileName As System.Windows.Forms.TextBox
    Public WithEvents LabelResultFittedSphere As Label
    Public WithEvents ResultFittedSphere As System.Windows.Forms.Label
    Public WithEvents LabelResultAllSelectedSphere As Label
    Public WithEvents ResultAllSelectedSphere As System.Windows.Forms.Label
End Class
