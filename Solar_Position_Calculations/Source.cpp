#include <iostream>
#define DEG_TO_RAD 0.01745329
#define PI 3.141592654
#define TWOPI 6.28318531

using namespace std;

long JulianDate(int year, int month, int day){
	long JD_whole;
	int A, B;
	if (month <= 2){
		year--;
		month += 12;
	}
	A = year / 100;
	B = 2 - A + A / 4;
	JD_whole = (long)(365.25*(year + 4716)) + (int)(30.6001*(month + 1)) + day + B - 1524;
	return (JD_whole);
}

int main(){
	int hour, minute = 0, second = 0, month = 6, day = 21, year = 2015, zone = 5;
	float Lon = -75 * DEG_TO_RAD, Lat = 40 * DEG_TO_RAD;
	float T, JD_frac, L0, M, e, C, L_true, f, R, GrHrAngle, Obl, RA, Decl, HrAngle, elev, azimuth;
	long JD_whole, JDx;
	
	cout << "Longtitude and latitude " << Lon / DEG_TO_RAD << " " << Lat / DEG_TO_RAD << endl;
	cout << "year, month, day, local hour, minute, second, elevation, azimuth" << endl;

	for (hour = 10; hour < 24; hour++){
		JD_whole = JulianDate(year, month, day);
		JD_frac = (hour + minute / 60. + second / 3600.) / 24. - .5;
		T = JD_whole - 2451545;
		T = (T + JD_frac) / 36525.;
		L0 = DEG_TO_RAD * fmod(280.46645 + 36000.76983 * T, 360);
		M = DEG_TO_RAD * fmod(357.5291 + 35999.0503*T, 360);
		e = 0.016708617 - 0.000042037 * T;
		C = DEG_TO_RAD * ((1.9146 - 0.004847*T) * sin(M) + (0.019993 - 0.000101*T) * sin(2 * M) + 0.00029 * sin(3 * M));
		f = M + C;
		Obl = DEG_TO_RAD * (23 + 26 / 60. + 21.448 / 3600. - 46.815 / 3600 * T);
		JDx = JD_whole - 2451545;
		GrHrAngle = 280.46061837 + (360 * JDx) % 360 + .98564736629*JDx + 360.98564736629*JD_frac;
		GrHrAngle = fmod(GrHrAngle, 360.);
		L_true = fmod(C + L0, TWOPI);
		R = 1.000001018*(1 - e*e) / (1 + e*cos(f));
		RA = atan2(sin(L_true) * cos(Obl), cos(L_true));
		Decl = asin(sin(Obl)*sin(L_true));
		HrAngle = DEG_TO_RAD*GrHrAngle + Lon - RA;
		elev = asin(sin(Lat)*sin(Decl) + cos(Lat)*(cos(Decl)*cos(HrAngle)));
		azimuth = PI + atan2(sin(HrAngle), cos(HrAngle)*sin(Lat) - tan(Decl)*cos(Lat));

		cout << year << "    " << month << "    " << day << "        " << hour - zone << "	 "
			<< minute << "	 " << second << "      " << elev / DEG_TO_RAD << "  " << azimuth / DEG_TO_RAD << endl;
	}

	system("pause");
	return 0;
}