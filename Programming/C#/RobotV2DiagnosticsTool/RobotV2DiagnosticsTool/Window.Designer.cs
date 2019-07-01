namespace RobotV2DiagnosticsTool
{
    partial class Window
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("LightSensor Array 1");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("LightSensor Array 2");
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("LightSensor Array 3");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("Board 1", new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2,
            treeNode3});
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("Motor Controller");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("Lightgate");
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("Board 2", new System.Windows.Forms.TreeNode[] {
            treeNode5,
            treeNode6});
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("IR Sensor Array 1");
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("IR Sensor Array 2");
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("IR Sensor Array 3");
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("Board 3", new System.Windows.Forms.TreeNode[] {
            treeNode8,
            treeNode9,
            treeNode10});
            System.Windows.Forms.TreeNode treeNode12 = new System.Windows.Forms.TreeNode("Teensy 3.5");
            System.Windows.Forms.TreeNode treeNode13 = new System.Windows.Forms.TreeNode("Board 4", new System.Windows.Forms.TreeNode[] {
            treeNode12});
            System.Windows.Forms.TreeNode treeNode14 = new System.Windows.Forms.TreeNode("Robot", new System.Windows.Forms.TreeNode[] {
            treeNode4,
            treeNode7,
            treeNode11,
            treeNode13});
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.soccerRobotToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ConnectionBtn = new System.Windows.Forms.ToolStripMenuItem();
            this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.RobotDeviceList = new System.Windows.Forms.TreeView();
            this.timerUpdate = new System.Windows.Forms.Timer(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.BoardImage = new System.Windows.Forms.PictureBox();
            this.LightSensorDisplayBtn = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BoardImage)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.soccerRobotToolStripMenuItem,
            this.toolsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(4, 1, 0, 1);
            this.menuStrip1.Size = new System.Drawing.Size(771, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // soccerRobotToolStripMenuItem
            // 
            this.soccerRobotToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ConnectionBtn});
            this.soccerRobotToolStripMenuItem.Name = "soccerRobotToolStripMenuItem";
            this.soccerRobotToolStripMenuItem.Size = new System.Drawing.Size(86, 22);
            this.soccerRobotToolStripMenuItem.Text = "SoccerRobot";
            // 
            // ConnectionBtn
            // 
            this.ConnectionBtn.Name = "ConnectionBtn";
            this.ConnectionBtn.Size = new System.Drawing.Size(119, 22);
            this.ConnectionBtn.Text = "Connect";
            this.ConnectionBtn.Click += new System.EventHandler(this.ToggleConnection);
            // 
            // toolsToolStripMenuItem
            // 
            this.toolsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.LightSensorDisplayBtn});
            this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
            this.toolsToolStripMenuItem.Size = new System.Drawing.Size(47, 22);
            this.toolsToolStripMenuItem.Text = "Tools";
            // 
            // RobotDeviceList
            // 
            this.RobotDeviceList.Dock = System.Windows.Forms.DockStyle.Left;
            this.RobotDeviceList.Location = new System.Drawing.Point(0, 24);
            this.RobotDeviceList.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.RobotDeviceList.Name = "RobotDeviceList";
            treeNode1.Name = "LightSensor1";
            treeNode1.Text = "LightSensor Array 1";
            treeNode2.Name = "LightSensor2";
            treeNode2.Text = "LightSensor Array 2";
            treeNode3.Name = "LightSensor3";
            treeNode3.Text = "LightSensor Array 3";
            treeNode4.Name = "Board1Main";
            treeNode4.Text = "Board 1";
            treeNode4.ToolTipText = "Light Sensor Board";
            treeNode5.Name = "MotorController";
            treeNode5.Text = "Motor Controller";
            treeNode6.Name = "LightgateSensor";
            treeNode6.Text = "Lightgate";
            treeNode7.Name = "Board2Main";
            treeNode7.Text = "Board 2";
            treeNode7.ToolTipText = "Motor Controller & Lightgate Board";
            treeNode8.Name = "IRSensor1";
            treeNode8.Text = "IR Sensor Array 1";
            treeNode9.Name = "IRSensor2";
            treeNode9.Text = "IR Sensor Array 2";
            treeNode10.Name = "IRSensor3";
            treeNode10.Text = "IR Sensor Array 3";
            treeNode11.Name = "Board3Main";
            treeNode11.Text = "Board 3";
            treeNode11.ToolTipText = "IR Sensor Board";
            treeNode12.Name = "Teensy";
            treeNode12.Text = "Teensy 3.5";
            treeNode13.Name = "Board4Main";
            treeNode13.Text = "Board 4";
            treeNode13.ToolTipText = "Main Board";
            treeNode14.Checked = true;
            treeNode14.ForeColor = System.Drawing.Color.Black;
            treeNode14.Name = "MainRobot";
            treeNode14.Text = "Robot";
            this.RobotDeviceList.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode14});
            this.RobotDeviceList.Size = new System.Drawing.Size(167, 445);
            this.RobotDeviceList.TabIndex = 1;
            this.RobotDeviceList.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.RobotDeviceList_AfterSelect);
            // 
            // timerUpdate
            // 
            this.timerUpdate.Enabled = true;
            this.timerUpdate.Tick += new System.EventHandler(this.UpdateVisualData);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Controls.Add(this.BoardImage);
            this.panel1.Location = new System.Drawing.Point(170, 21);
            this.panel1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(601, 447);
            this.panel1.TabIndex = 2;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 259);
            this.panel2.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(601, 188);
            this.panel2.TabIndex = 1;
            // 
            // BoardImage
            // 
            this.BoardImage.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.BoardImage.Dock = System.Windows.Forms.DockStyle.Top;
            this.BoardImage.Image = global::RobotV2DiagnosticsTool.Properties.Resources.Robot;
            this.BoardImage.Location = new System.Drawing.Point(0, 0);
            this.BoardImage.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.BoardImage.Name = "BoardImage";
            this.BoardImage.Size = new System.Drawing.Size(601, 259);
            this.BoardImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.BoardImage.TabIndex = 0;
            this.BoardImage.TabStop = false;
            // 
            // LightSensorDisplayBtn
            // 
            this.LightSensorDisplayBtn.Name = "LightSensorDisplayBtn";
            this.LightSensorDisplayBtn.Size = new System.Drawing.Size(180, 22);
            this.LightSensorDisplayBtn.Text = "Light Sensor View";
            this.LightSensorDisplayBtn.Click += new System.EventHandler(this.LightSensorDisplayBtn_Click);
            // 
            // Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(771, 469);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.RobotDeviceList);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "Window";
            this.Text = "Robot V2 Diagnostics Tool";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.BoardImage)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem soccerRobotToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ConnectionBtn;
        private System.Windows.Forms.TreeView RobotDeviceList;
        private System.Windows.Forms.Timer timerUpdate;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox BoardImage;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem LightSensorDisplayBtn;
    }
}

