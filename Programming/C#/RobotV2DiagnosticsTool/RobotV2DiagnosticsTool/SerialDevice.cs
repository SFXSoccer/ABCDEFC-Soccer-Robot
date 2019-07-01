using System;
using System.IO;
using System.IO.Ports;
using System.Text.RegularExpressions;

namespace RobotV2DiagnosticsTool
{
    public class SerialDevice : SerialPort
    {
        enum Bytes : byte
        {
            STARTBYTE = 0xA0,
            ENDBYTE = 0xA1
        }

        public SerialDevice(string comPort, int baudRate)
        {
            base.PortName = comPort;
            base.BaudRate = baudRate;

            base.DataReceived += new SerialDataReceivedEventHandler(PortDataReceived);
        }

        public void PortDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                while (base.BytesToRead >= 3)
                {
                    if (base.ReadByte() == (byte)Bytes.STARTBYTE)
                    {
                        if (base.ReadByte() == 0x00)
                        {
                            Data.ConnectedDevices = (byte)base.ReadByte();
                            Data.LightSensorArrayData[0] = (byte)base.ReadByte();
                            Data.LightSensorArrayData[1] = (byte)base.ReadByte();
                            Data.LightSensorArrayData[2] = (byte)base.ReadByte();
                            base.ReadByte();
                        }
                        else if (base.ReadByte() == (byte)Command.Commands.DIAGNOSIS_I2C_SCAN)
                        {
                            int value = base.ReadByte();
                            while (value != (byte)Bytes.ENDBYTE)
                            {
                                Console.WriteLine(value);
                                value = base.ReadByte();
                            }
                        }
                    }
                }
            }
            catch (IOException ex)
            {
                Console.WriteLine(ex);
            }
        }

        public void Connect(string portName, int baudRate, int dataBits, StopBits stopBits, Handshake handshake, Parity parity)
        {
            PortName = portName;
            BaudRate = baudRate;
            DataBits = dataBits;
            StopBits = stopBits;
            Handshake = handshake;
            Parity = parity;

            try
            {
                Program.SerialDevice.Open();
                Console.WriteLine("Connected");
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

        public void Disconnect()
        {
            try
            {
                Close();
                Console.WriteLine("Disconnected");
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
