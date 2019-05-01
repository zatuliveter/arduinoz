using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RobotArmEmulator
{
    public class PointD
    {
        public double X { get; private set; }
        public double Y { get; private set; }

        public PointD(double x, double y)
        {
            X = x;
            Y = y;
        }

        public Point GetPoint()
        {
            return new Point(Convert.ToInt32(X), Convert.ToInt32(Y));
        }

        public static PointD operator +(PointD p1, PointD p2) 
        { 
            return new PointD(p1.X + p2.X, p1.Y + p2.Y);
        } 

        public override string ToString()
        {
            return $"[x={X},y={Y}]";
        }
    }
}
