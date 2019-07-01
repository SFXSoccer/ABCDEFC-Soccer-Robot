using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotV2DiagnosticsTool
{
    public partial class SelectComm : Form
    {
        public SelectComm()
        {
            InitializeComponent();
        }

        private void SelectComm_Load(object sender, EventArgs e)
        {
            string[] ArrayComPortsNames = null;
            int index = -1;
            string ComPortName = null;

            ArrayComPortsNames = SerialPort.GetPortNames();
            do
            {
                index += 1;
                cboPorts.Items.Add(ArrayComPortsNames[index]);
            }

            while (!((ArrayComPortsNames[index] == ComPortName)
                          || (index == ArrayComPortsNames.GetUpperBound(0))));
            Array.Sort(ArrayComPortsNames);

            //want to get first out
            if (index == ArrayComPortsNames.GetUpperBound(0))
            {
                ComPortName = ArrayComPortsNames[0];
            }
            cboPorts.Text = ArrayComPortsNames[0];
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            string[] ArrayComPortsNames = null;
            int index = -1;
            string ComPortName = null;

            cboPorts.Items.Clear();
            ArrayComPortsNames = SerialPort.GetPortNames();
            do
            {
                index += 1;
                cboPorts.Items.Add(ArrayComPortsNames[index]);
            }

            while (!((ArrayComPortsNames[index] == ComPortName)
                          || (index == ArrayComPortsNames.GetUpperBound(0))));
            Array.Sort(ArrayComPortsNames);

            //want to get first out
            if (index == ArrayComPortsNames.GetUpperBound(0))
            {
                ComPortName = ArrayComPortsNames[0];
            }
            cboPorts.Text = ArrayComPortsNames[0];
        }

        private void Connect(object sender, EventArgs e)
        {
            try
            {
                Program.SerialDevice.Connect(cboPorts.Text.ToString(), int.Parse(cboBaudRate.Text), int.Parse(cboDataBits.Text), (StopBits)Enum.Parse(typeof(StopBits), cboStopBits.Text), Handshake.None, Parity.None);
                Console.WriteLine("Connected");
                this.Close();
            }
            catch (UnauthorizedAccessException ex)
            {
                Console.WriteLine("Error: Port {0} is in use", Program.SerialDevice.PortName);
            }
            catch (Exception ex)
            {
                Console.WriteLine("SerialDevice exception: " + ex);
            }
        }
    }
}
