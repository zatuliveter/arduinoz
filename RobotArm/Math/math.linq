<Query Kind="Program" />

//https://otvet.mail.ru/question/24388379

void Main()
{
	double ac = 25;
	double ab = 15;
	double bc = 15;
	
	double a = (Math.Pow(ac, 2) - Math.Pow(ab, 2) + Math.Pow(bc, 2)) 
				/ (2 * ac * bc);
	double b = (Math.Pow(ab, 2) - Math.Pow(ac, 2) + Math.Pow(bc, 2)) 
			/ (2 * ab * bc);
	double c = (Math.Pow(ab, 2) - Math.Pow(bc, 2) + Math.Pow(ac, 2)) 
			/ (2 * ab * ac);
	
	a.Dump();	
	b.Dump();	
	c.Dump();
	
	double a1 = RadianToDegree(Math.Acos(a)).Dump();
	double b1 = RadianToDegree(Math.Acos(b)).Dump();
	double c1 = RadianToDegree(Math.Acos(c)).Dump();
	
	double total = a1 + b1 + c1;
	
	total.Dump();
}


double RadianToDegree(double angle)
{
   return angle * (180.0 / Math.PI);
}