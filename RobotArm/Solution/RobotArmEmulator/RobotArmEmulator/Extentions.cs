using System;
using System.Drawing;

namespace RobotArmEmulator
{
    public static class Extentions
    {
        public static double RadianToDegree(this double angle)
        {
            return angle * (180.0 / Math.PI);
        }
        public static double Round(this double val)
        {
            return Math.Round(val, 2);
        }
        public static Point Diff(this Point point, Point diff)
        {
            return new Point(point.X + diff.X, point.Y + diff.Y);
        }                
        public static Point InvertY(this Point point)
        {
            return new Point(point.X, -point.Y);
        }       
        public static PointD Mult(this PointD point, int scale)
        {            
            return new PointD(point.X * scale, point.Y * scale);
        }
    }
}
