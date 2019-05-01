using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotArmEmulator
{
    public partial class Form1 : Form
    {
        ArmCalcs calc = new ArmCalcs();
        Point diffPoint = new Point(350, 250);

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {            
            var g = e.Graphics;
                        
            g.DrawLine(
                Pens.Red, 
                calc.ap.Mult(10).GetPoint().InvertY().Diff(diffPoint),
                calc.bp.Mult(10).GetPoint().InvertY().Diff(diffPoint));

            g.DrawLine(
                Pens.Green, 
                calc.bp.Mult(10).GetPoint().InvertY().Diff(diffPoint),
                calc.cp.Mult(10).GetPoint().InvertY().Diff(diffPoint));
                        
            g.DrawLine(
                Pens.Blue, 
                calc.cp.Mult(10).GetPoint().InvertY().Diff(diffPoint),
                calc.dp.Mult(10).GetPoint().InvertY().Diff(diffPoint));
        }


        private void ApplyChanges()
        {            
            calc.SetPos((int)XVal.Value, (int)YVal.Value);

            txtOutput.Clear();
            txtOutput.AppendText(calc.ToString());

            Refresh();
        }

        private void XVal_ValueChanged(object sender, EventArgs e)
        {
            ApplyChanges();
        }

        private void YVal_ValueChanged(object sender, EventArgs e)
        {
            ApplyChanges();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ApplyChanges();
        }
    }
}
