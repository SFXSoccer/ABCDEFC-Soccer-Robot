using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RobotV2DiagnosticsTool
{
    public static class Command
    {
        public enum Commands : byte
        {
            DIAGNOSIS_START = 0xA5,
            DIAGNOSIS_STOP = 0xA6,
            DIAGNOSIS_I2C_SCAN = 0xA7,
        }

        public static void Send(Commands cmd, params byte[] data)
        {
            byte[] sendBytes = new byte[data.Length + 1];
            sendBytes[0] = (byte)cmd;
            for (int i = 0; i < data.Length; i++)
                sendBytes[i + 1] = data[i];
            Program.SerialDevice.Write(sendBytes, 0, sendBytes.Length);
        }
    }
}
