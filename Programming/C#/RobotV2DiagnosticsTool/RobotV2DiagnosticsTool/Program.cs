using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotV2DiagnosticsTool
{
    static class Program
    {
        public static SerialDevice SerialDevice { get; set; } = new SerialDevice("COMM3", 9600);
        public static Window Window { get; set; }

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(Window = new Window());
        }
    }
}
