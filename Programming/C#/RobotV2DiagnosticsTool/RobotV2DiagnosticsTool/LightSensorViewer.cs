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
    public partial class LightSensorViewer : Form
    {
        public LightSensorViewer()
        {
            InitializeComponent();
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            float angle = 0;
            for (int i = 0; i < 24; i++)
            {
                Point p = VirtualPoint((int)(48 * Math.Sin(angle * (Math.PI / 180))), (int)(48 * Math.Cos(angle * (Math.PI / 180))), 10);
                if (i < 8)
                    e.Graphics.FillEllipse(Data.LightSensorArrayData[0] >> 7 - i != 0 ? Brushes.Red : Brushes.DimGray, p.X, p.Y, 10, 10);
                else if (i < 16)
                    e.Graphics.FillEllipse(Data.LightSensorArrayData[1] >> 7 - (i - 8) != 0 ? Brushes.Red : Brushes.DimGray, p.X, p.Y, 10, 10);
                else if (i < 24)
                    e.Graphics.FillEllipse(Data.LightSensorArrayData[2] >> 7 - (i - 16) != 0 ? Brushes.Red : Brushes.DimGray, p.X, p.Y, 10, 10);
                angle += 15;
            }
            Refresh();
        }

        private Point VirtualPoint(int x, int y, int size = 0) { return new Point((Width / 2 + x) - size, (Height / 2 + y) - size); }
    }
}
