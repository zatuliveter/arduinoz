using System;
using System.Drawing;

namespace RobotArmEmulator
{
    class ArmCalcs
    {
        public double angle { get; private set; }

        public double a { get; private set; }
        public double b { get; private set; }
        public double c { get; private set; }

        public double ac { get; private set; }
        public double ab { get; private set; } = 15;
        public double bc { get; private set; } = 15;
        public double cd { get; private set; } = 15;
        
        public PointD ap {get;set;}
        public PointD bp {get;set;}
        public PointD cp {get;set;}
        public PointD dp {get;set;}

        public void SetPos(int x, int y)
        {
            ac = Math.Sqrt(Math.Pow(x, 2) + Math.Pow(y, 2));

            //angle = Math.Asin(x / ac);
            angle = Math.Atan2(y, x);

            a = Math.Acos((Math.Pow(ac, 2) - Math.Pow(ab, 2) + Math.Pow(bc, 2))
                    / (2 * ac * bc));

            //b = Math.Acos((Math.Pow(ab, 2) - Math.Pow(ac, 2) + Math.Pow(bc, 2))
            //        / (2 * ab * bc));

            //c = Math.Acos((Math.Pow(ab, 2) - Math.Pow(bc, 2) + Math.Pow(ac, 2))
            //        / (2 * ab * ac));

            ap = new PointD(0, 0);
            
            cp = new PointD(
                ac * Math.Sin(angle),
                ac * Math.Cos(angle)
                );

            bp = new PointD(
                ab * Math.Sin(angle - a ),
                ab * Math.Cos(angle - a )
                );

            dp = cp + new PointD(cd, 0);
        }

        public override string ToString()
        {
            return $@"angle = {angle.RadianToDegree().Round()}
ac = {ac.Round()}
a = {a.RadianToDegree().Round()}
b = {b.RadianToDegree().Round()}
c = {c.RadianToDegree().Round()}
ap = {ap}
bp = {bp}
cp = {cp}
";
        }
    }
}
