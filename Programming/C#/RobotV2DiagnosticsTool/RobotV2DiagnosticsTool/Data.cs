using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RobotV2DiagnosticsTool
{
    public static class Data
    {
        public static byte ConnectedDevices = 0x00;
        public static byte[] LightSensorArrayData = { 0x00, 0x00, 0x00 };

        public static bool IsDeviceConnected(byte device)
        {
            return (ConnectedDevices & (1 << device)) != 0;
        }
    }
}
