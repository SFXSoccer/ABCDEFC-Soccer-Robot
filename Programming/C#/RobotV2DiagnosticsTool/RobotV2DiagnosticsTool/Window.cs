using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotV2DiagnosticsTool
{
    public partial class Window : Form
    {
        public Window()
        {
            InitializeComponent();
        }

        private void ToggleConnection(object sender, EventArgs e)
        {
            if (!Program.SerialDevice.IsOpen)
            {
                SelectComm selectComm = new SelectComm();
                selectComm.ShowDialog();
                Text = string.Format("Robot V2 Diagnostics Tool | {0}", Program.SerialDevice.PortName);

                if (Program.SerialDevice.IsOpen)
                {
                    Console.WriteLine("Connecting to SoccerRobot");
                    Command.Send(Command.Commands.DIAGNOSIS_START);

                    ToolStripMenuItem item = sender as ToolStripMenuItem;
                    item.Text = "Disconnect";
                }
            }
            else if (Program.SerialDevice.IsOpen)
            {
                Console.WriteLine("Disconnecting from SoccerRobot");
                Command.Send(Command.Commands.DIAGNOSIS_STOP);
                Program.SerialDevice.Disconnect();

                foreach (TreeNode nodes in RobotDeviceList.Nodes[0].Nodes)
                    foreach (TreeNode node in nodes.Nodes)
                        node.ForeColor = Color.Black;

                ToolStripMenuItem item = sender as ToolStripMenuItem;
                item.Text = "Connect";
            }
        }

        private void UpdateVisualData(object sender, EventArgs e)
        {
            if (Program.SerialDevice.IsOpen)
            {
                // Light sensor Arrays
                RobotDeviceList.Nodes[0].Nodes[0].Nodes[0].ForeColor = Data.IsDeviceConnected(5) ? Color.Green : Color.Red;
                RobotDeviceList.Nodes[0].Nodes[0].Nodes[1].ForeColor = Data.IsDeviceConnected(6) ? Color.Green : Color.Red;
                RobotDeviceList.Nodes[0].Nodes[0].Nodes[2].ForeColor = Data.IsDeviceConnected(7) ? Color.Green : Color.Red;

                // Motor Controller and Lightgate
                RobotDeviceList.Nodes[0].Nodes[1].Nodes[0].ForeColor = Data.IsDeviceConnected(4) ? Color.Green : Color.Red;
                RobotDeviceList.Nodes[0].Nodes[1].Nodes[1].ForeColor = Data.IsDeviceConnected(4) ? Color.Green : Color.Red;

                // IR sensor Arrays
                RobotDeviceList.Nodes[0].Nodes[2].Nodes[0].ForeColor = Data.IsDeviceConnected(1) ? Color.Green : Color.Red;
                RobotDeviceList.Nodes[0].Nodes[2].Nodes[1].ForeColor = Data.IsDeviceConnected(2) ? Color.Green : Color.Red;
                RobotDeviceList.Nodes[0].Nodes[2].Nodes[2].ForeColor = Data.IsDeviceConnected(3) ? Color.Green : Color.Red;

                // Main board
                RobotDeviceList.Nodes[0].Nodes[3].Nodes[0].ForeColor = Data.IsDeviceConnected(0) ? Color.Green : Color.Red;
            }
        }

        private void RobotDeviceList_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (RobotDeviceList.SelectedNode.Text == "Robot")
                BoardImage.Image = Properties.Resources.Robot;
            else if (RobotDeviceList.SelectedNode.Text == "Board 1")
                BoardImage.Image = Properties.Resources.Board_1;
            else if (RobotDeviceList.SelectedNode.Text == "Board 2")
                BoardImage.Image = Properties.Resources.Board_2;
            else if (RobotDeviceList.SelectedNode.Text == "Board 3")
                BoardImage.Image = Properties.Resources.Board_3;
            else if (RobotDeviceList.SelectedNode.Text == "Board 4")
                BoardImage.Image = Properties.Resources.Board_4;
            else if (RobotDeviceList.SelectedNode.Parent != null)
            {
                if (RobotDeviceList.SelectedNode.Parent.Text == "Board 1")
                    BoardImage.Image = Properties.Resources.Board_1;
                else if (RobotDeviceList.SelectedNode.Parent.Text == "Board 2")
                    BoardImage.Image = Properties.Resources.Board_2;
                else if (RobotDeviceList.SelectedNode.Parent.Text == "Board 3")
                    BoardImage.Image = Properties.Resources.Board_3;
                else if (RobotDeviceList.SelectedNode.Parent.Text == "Board 4")
                    BoardImage.Image = Properties.Resources.Board_4;
            }
        }

        private void LightSensorDisplayBtn_Click(object sender, EventArgs e)
        {
            LightSensorViewer lightSensorViewer = new LightSensorViewer();
            lightSensorViewer.Show();
        }
    }
}
