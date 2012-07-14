#include "f2f3D.h"

void f2f3D::fShift() {
	pointX += shiftX;
	pointY += shiftY;
	pointZ += shiftZ;
	if (isnan(pointX)) {pointX = 0;}
	if (isnan(pointY)) {pointY = 0;}
	if (isnan(pointZ)) {pointZ = 0;}
}

void f2f3D::fZoom() {
	pointX *= zoomX;
	pointY *= zoomY;
	pointZ *= zoomZ;
	if (isnan(pointX)) {pointX = 0;}
	if (isnan(pointY)) {pointY = 0;}
	if (isnan(pointZ)) {pointZ = 0;}
}

void f2f3D::fProjection() {
	double a, b, c, d, t[13];
	bool m1, m2;
	if (projectionNewAngel) {
		t[0] = cos(projectionAngelX);
		t[1] = sin(projectionAngelX);
		t[2] = cos(projectionAngelY);
		t[3] = sin(projectionAngelY);
		t[4] = cos(projectionAngelZ);
		t[5] = sin(projectionAngelZ);
	}
	t[6] = pointX-projectionCameraX;
	t[7] = pointY-projectionCameraY;
	t[8] = pointZ-projectionCameraZ;
	/* version one
	t[9] = t[5]*t[7]+t[4]*t[6];
	t[10] = t[2]*t[8]+t[3]*t[9];
	t[11] = t[4]*t[7]-t[5]*t[6];
	t[12] = projectionViewerZ/(t[0]*t[10]-t[1]*t[11]);
	pointX = (t[2]*t[9]-t[3]*t[8]-projectionViewerX)*t[12];
	pointY = (t[1]*t[10]+t[0]*t[11]-projectionViewerY)*t[12];
	*/
	t[9] = -t[5]*t[7]+t[4]*t[6];
	t[10] = -t[2]*t[8]+t[3]*t[9];
	t[11] = t[4]*t[7]+t[5]*t[6];
	t[12] = projectionViewerZ/(-t[0]*t[10]+t[1]*t[11]);
	pointX = (t[2]*t[9]+t[3]*t[8]-projectionViewerX)*t[12];
	pointY = (t[1]*t[10]+t[0]*t[11]-projectionViewerY)*t[12];
	if (isnan(pointX) || isnan(pointY)) {
		t[0] = isnan(t[0]) ? 1 : t[0];
		t[1] = isnan(t[1]) ? 0 : t[1];
		t[2] = isnan(t[2]) ? 1 : t[2];
		t[3] = isnan(t[3]) ? 0 : t[3];
		t[4] = isnan(t[4]) ? 1 : t[4];
		t[5] = isnan(t[5]) ? 0 : t[5];
		t[6] = isnan(t[6]) ? 0 : t[6];
		t[7] = isnan(t[7]) ? 0 : t[7];
		t[8] = isnan(t[8]) ? 0 : t[8];
		a = isnan(t[5]*t[7]) ? 0 : (t[5]*t[7]);
		b = isnan(t[4]*t[6]) ? 0 : (t[4]*t[6]);
		t[9] = isnan(a+b) ? 0 : (a+b);
		a = isnan(t[2]*t[8]) ? 0 : (t[2]*t[8]);
		b = isnan(t[3]*t[9]) ? 0 : (t[3]*t[9]);
		t[10] = isnan(a+b) ? 0 : (a+b);
		a = isnan(t[4]*t[7]) ? 0 : (t[4]*t[7]);
		b = isnan(t[5]*t[6]) ? 0 : (t[5]*t[6]);
		t[11] = isnan(a-b) ? 0 : (a-b);
		a = isnan(t[0]*t[10]) ? 0 : (t[0]*t[10]);
		b = isnan(t[1]*t[11]) ? 0 : (t[1]*t[11]);
		c = isnan(a-b) ? 0 : (a-b);	
		if (isnan(projectionViewerZ/c)) {
			m1 = (projectionViewerZ < 0) ? true : false;
			m2 = (c < 0) ? true : false;
			if (fabs(c) < 0.00001) {
				t[12] = ((m1 && !m2) || (!m1 && m2)) ? -INFINITY : INFINITY;
			} else {
				t[12] = ((m1 && !m2) || (!m1 && m2)) ? -1 : 1;
			}
		} else {
			t[12] = projectionViewerZ/c;
		}	
	}
	if (isnan(pointX)) {
		a = isnan(t[2]*t[9]) ? 0 : (t[2]*t[9]);
		b = isnan(t[3]*t[8]) ? 0 : (t[3]*t[8]);
		c = isnan(a-b) ? 0 : (a-b);
		d = isnan(c-projectionViewerX) ? 0 : (c-projectionViewerX);
		pointX = isnan(d*t[12]) ? 0 : (d*t[12]);
	}
	if (isnan(pointY)) {
		a = isnan(t[1]*t[10]) ? 0 : (t[1]*t[10]);
		b = isnan(t[0]*t[11]) ? 0 : (t[0]*t[11]);
		c = isnan(a+b) ? 0 : (a+b);
		d = isnan(c-projectionViewerY) ? 0 : (c-projectionViewerY);
		pointY = isnan(d*t[12]) ? 0 : (d*t[12]);
	}	
}

void f2f3D::fRotation() {
	bool goRotate;
	double x, y, z, l;
	double unitVektorRotateX, unitVektorRotateY, unitVektorRotateZ;
	double angelRotate1, angelRotate2, angelRotate3;
	double deltaX, deltaY, deltaZ;
	goRotate = true;
	if (rotationNewAxis) {
		x = rotationPoint2X-rotationPoint1X;
		y = rotationPoint2Y-rotationPoint1Y;
		z = rotationPoint2Z-rotationPoint1Z;
		l = sqrt(x*x+y*y+z*z);
		if (l < 0.00001) {
			goRotate = false;
		} else {
			unitVektorRotateX = x/l;
			unitVektorRotateY = y/l;
			unitVektorRotateZ = z/l;
		}
	}
	if (rotationNewAngel) {
		if (fabs(rotationAngel) < 0.00001) {
			goRotate = false;
		} else {
			angelRotate1 = cos(rotationAngel);
			angelRotate2 = 1-angelRotate1;
			angelRotate3 = sin(rotationAngel);
		}
	}
	if (goRotate) {
		deltaX = pointX-rotationPoint1X;
		deltaY = pointY-rotationPoint1Y;
		deltaZ = pointZ-rotationPoint1Z;
		pointX = (unitVektorRotateX*unitVektorRotateX*angelRotate2+angelRotate1)*deltaX+(unitVektorRotateX*unitVektorRotateY*angelRotate2-unitVektorRotateZ*angelRotate3)*deltaY+(unitVektorRotateX*unitVektorRotateZ*angelRotate2+unitVektorRotateY*angelRotate3)*deltaZ+rotationPoint1X;
		pointY = (unitVektorRotateY*unitVektorRotateX*angelRotate2+unitVektorRotateZ*angelRotate3)*deltaX+(unitVektorRotateY*unitVektorRotateY*angelRotate2+angelRotate1)*deltaY+(unitVektorRotateY*unitVektorRotateZ*angelRotate2-unitVektorRotateX*angelRotate3)*deltaZ+rotationPoint1Y;
		pointZ = (unitVektorRotateZ*unitVektorRotateX*angelRotate2-unitVektorRotateY*angelRotate3)*deltaX+(unitVektorRotateZ*unitVektorRotateY*angelRotate2+unitVektorRotateX*angelRotate3)*deltaY+(unitVektorRotateZ*unitVektorRotateZ*angelRotate2+angelRotate1)*deltaZ+rotationPoint1Z;
	}
}

void f2f3D::fTranslate() {
	double t, swap;
	double savePoint;
	savePoint = pointX;
	t = pointY/sqrt(translatePointSlope*translatePointSlope+1);
	if (fabs(t) < 0.00001) {
		if (t > 0) {
			pointX += pointY;
		} else {
			pointX -= pointY;
		}
	} else {
		pointX += translatePointSlope*t;
	}
	pointY = translatePointArg-t;
	if (isnan(pointX) || isnan(pointY)) {
			if isnan(t) {t = 1;}
			swap = isnan(translatePointSlope*t) ? 0 : (translatePointSlope*t);
			pointX = savePoint;
			pointX = isnan(pointX+swap) ? 0 : (pointX+swap);
			pointY = isnan(translatePointArg-t) ? 0 : (translatePointArg-t);
	}
}

void f2f3D::fCentral() {
	double t[9], savePointX, savePointY;
	double swap, a, b;
	bool i1, i2, z1, z2, m1, m2;
	savePointX = pointX;
	savePointY = pointY;
	t[0] = centralCenterX-pointX;
	t[1] = centralCenterY-pointY;
	t[2] = centralAxisX-pointX;
	t[3] = centralAxisY-pointY;
	t[4] = sqrt(t[0]*t[0]+t[1]*t[1]);	
	t[5] = sqrt(t[2]*t[2]+t[3]*t[3]);
	if (centralTriggerCenter && ((pointX > centralCenterX) || (pointY > centralCenterY))) {t[4] = -t[4];}
	if (centralTriggerAxis && ((pointX > centralAxisX) || (pointY > centralAxisY))) {t[5] = -t[5];}	
	t[6] = t[4]*(1-exp(t[5]/t[4]));
	t[7] = (centralCenterY-centralAxisY)/(centralCenterX-centralAxisX);
	t[8] = sqrt(t[7]*t[7]+1);
	pointX += centralMoveX+t[6]/t[8];
	pointY += centralMoveY+t[6]*t[8];
	if (isnan(pointX) || isnan(pointY)) {
		if (isnan(t[0])) {t[0] = 0;}
		if (isnan(t[1])) {t[1] = 0;}
		if (isnan(t[2])) {t[2] = 0;}
		if (isnan(t[3])) {t[3] = 0;}
		if (isnan(t[4])) {t[4] = sqrt(t[0]*t[0]+t[1]*t[1]);}	
		if (isnan(t[5])) {t[5] = sqrt(t[2]*t[2]+t[3]*t[3]);}		
		swap = t[5]/t[4];
		if (isnan(swap)) {
			i1 = isinf(t[5]) ? true : false;
			i2 = isinf(t[4]) ? true : false;
			z1 = (fabs(t[5]) < 0.00001) ? true : false;
			z2 = (fabs(t[4]) < 0.00001) ? true : false;
			if ((i1 && i2) || (z1 && z2)) {
				swap = 1;
			}
			if (!z1 && z2) {
				swap = INFINITY;
			}
		}		
		t[6] = t[4]*(1-exp(swap));
		if (isnan(t[6])) {t[6] = 0;}		
		a = centralCenterY-centralAxisY;
		if (isnan(a)) {a = 0;}
		b = centralCenterX-centralAxisX;
		if (isnan(b)) {b = 0;}
		t[7] = a/b;
		if (isnan(t[7])) {
			i1 = isinf(a) ? true : false;
			i2 = isinf(b) ? true : false;
			z1 = (fabs(a) < 0.00001) ? true : false;
			z2 = (fabs(b) < 0.00001) ? true : false;
			m1 = (a < 0) ? true : false;
			m2 = (b < 0) ? true : false;
			if ((i1 && i2) || (z1 && z2)) {
				t[7] = ((m1 && !m2) || (!m1 && m2)) ? -1 : 1;
			}
			if (!z1 && z2) {
				t[7] = ((m1 && !m2) || (!m1 && m2)) ? -INFINITY : INFINITY;
			}
		}
		t[8] = sqrt(t[7]*t[7]+1);
		a = savePointX+centralMoveX;
		if (isnan(a)) {a = 0;}
		b = t[6]/t[8];
		if (isnan(b)) {
			b = (t[6] < 0) ? -1 : 1;
		}
		pointX = a+b;
		if (isnan(pointX)) {pointX = 0;}
		a = savePointY+centralMoveY;
		if (isnan(a)) {a = 0;}
		b = t[6]*t[8];
		if (isnan(b)) {b = 0;}
		pointY = a+b;
		if (isnan(pointY)) {pointY = 0;}		
	}
}

void f2f3D::fPlane() {
    double unitVektorXx, unitVektorXy, unitVektorXz;
	double unitVektorYx, unitVektorYy, unitVektorYz;
	double vektorYx, vektorYy, vektorYz;
    double x, y, z, l;
	double s[12];
    if (planeNewPlane) {
        x = planePoint2X-planePoint1X;
        y = planePoint2Y-planePoint1Y;
        z = planePoint2Z-planePoint1Z;
        l = sqrt(x*x+y*y+z*z);
        unitVektorXx = x/l;
        unitVektorXy = y/l;
        unitVektorXz = z/l;
        x = planePoint3X-planePoint1X;
        y = planePoint3Y-planePoint1Y;
        z = planePoint3Z-planePoint1Z;
        l = unitVektorXx*x+unitVektorXy*y+unitVektorXz*z;
        vektorYx = x-l*unitVektorXx;
        vektorYy = y-l*unitVektorXy;
        vektorYz = z-l*unitVektorXz;
		l = sqrt(vektorYx*vektorYx+vektorYy*vektorYy+vektorYz*vektorYz);
		unitVektorYx = vektorYx/l;
        unitVektorYy = vektorYy/l;
        unitVektorYz = vektorYz/l;
    }
    if (planeRotatePlane) {
		s[0] = cos(planeRotateAngel);
		s[1] = sin(planeRotateAngel);
		s[2] = 1-s[0];
		s[3] = unitVektorXx*unitVektorXy*s[2];
		s[4] = unitVektorXx*unitVektorXz*s[2];
		s[5] = unitVektorXy*unitVektorXz*s[2];
		s[6] = unitVektorXx*s[1];
		s[7] = unitVektorXy*s[1];
		s[8] = unitVektorXz*s[1];
		s[9] = unitVektorYx;
		s[10] = unitVektorYy;
		s[11] = unitVektorYz;
		unitVektorYx = (unitVektorXx*unitVektorXx*s[2]+s[0])*s[9]+(s[3]-s[8])*s[10]+(s[4]+s[7])*s[11];
		unitVektorYy = (s[3]+s[8])*s[9]+(unitVektorXy*unitVektorXy*s[2]+s[0])*s[10]+(s[5]-s[6])*s[11];
		unitVektorYz = (s[4]-s[7])*s[9]+(s[5]+s[6])*s[10]+(unitVektorXz*unitVektorXz*s[2]+s[0])*s[11];
    }
    x = pointX;
    y = pointY;
    pointX = planePoint1X+x*unitVektorXx+y*unitVektorYx;
    pointY = planePoint1Y+x*unitVektorXy+y*unitVektorYy;
    pointZ = planePoint1Z+x*unitVektorXz+y*unitVektorYz;
}

void f2f3D::fSet() {
	double os, is, a, b, c, d, swap;
	timeval tp;
	gettimeofday(&tp, 0);
	srand((unsigned)time(0));
	double t = RAND_MAX;
	double time[4];	
	time[0] = (tp.tv_usec/1000-500)*3.141592653589793;
	swap = sin(time[0]*rand()/t);
	time[1] = swap*10+10.1;
	time[2] = swap*10+10.1;
	time[3] = swap*5+5.1;	
	if (setNewControl) {
		os = outerCycleDimension+outerCycleExtension;
		is = innerCycleDimension+innerCycleExtension;
		s[0] = os*0.5;
		s[1] = is*0.5;
		s[2] = s[0]+s[1];
		s[3] = s[0]-s[1];
		s[4] = is/os+1;
		s[5] = is/os-1;
	}	
	a = (setPointX-setPointMinX)*2/outerCycleDimension;	
	switch(setGraph) {
		case 0:
			// simple Line
			pointX = setPointX;
			pointY = setPointY;
			break;
		case 1:
			// Cycloid
			pointX = setPointX+s[0]*sin(a);
			pointY = setPointY+s[0]*(1+cos(a));
			break;
		case 2:
			// Epicycloid
			b = s[4]*a;
			pointX = setPointX+s[2]*cos(a)-s[0]*cos(b);
			pointY = setPointY+s[2]*sin(a)-s[0]*sin(b);
			break;
		case 3:
			// Epicycloid variation
			b = s[4]*a;
			pointX = setPointX+s[2]*cos(a)+s[0]*cos(b);
			pointY = setPointY+s[2]*sin(a)-s[0]*sin(b);
			break;
		case 4:
			// Hypocycloid
			b = s[5]*a;
			pointX = setPointX+s[3]*cos(a)-s[1]*cos(b);
			pointY = setPointY+s[3]*sin(a)-s[1]*sin(b);
			break;
		case 5:
			// Hypocycloid variation
			b = s[5]*a;
			pointX = setPointX+s[3]*cos(a)+s[1]*cos(b);
			pointY = setPointY+s[3]*sin(a)-s[1]*sin(b);
			break;
		case 6:
			// Cardioid
			b = cos(a);
			pointX = setPointX+s[0]*b*(1+b);
			pointY = setPointY+s[0]*(1+sin(a)*(1+b));
			break;
		case 7:
			// Astroid
			b = cos(a);
			c = sin(a);
			pointX = setPointX+s[0]*b*b*b;
			pointY = setPointY+s[0]*(1+c*c*c);
			break;
		case 8:
			// Nephroid
			b = cos(a);
			c = sin(a);
			pointX = setPointX+s[0]*(1.5*b-b*b*b);
			pointY = setPointY+s[0]*c*c*c;
			break;
		case 9:
			// Nephroid variation
			b = cos(a);
			c = sin(a);
			pointX = setPointX+s[0]*(1.5*b+b*b*b);
			pointY = setPointY+s[0]*c*c*c;
			break;
		case 10:
			// Limacon
			b = cos(a);
			c = sin(a);
			d = s[0]*b+s[1];
			pointX = setPointX+b*d;
			pointY = setPointY+c*d;
			break;
		case 11:
			// Limacon variation
			b = cos(a);
			c = cos(2*a);
			d = os*b-s[0]*c;
			pointX = setPointX+d;
			pointY = setPointY+d;
			break;
		case 12:
			// Conchoid
			pointX = setPointX+s[1]+s[0]*cos(a);
			pointY = setPointY+s[1]*tan(a)+s[0]*sin(a);
			break;
		case 13:
			// Cissoid
			b = a*a;
			c = os*b/(1+b);
			pointX = setPointX+c;
			pointY = setPointY+b*c;
			break;
		case 14:
			// Strophoid
			b = a*a;
			c = os*(b-1)/(1+b);
			pointX = setPointX+c;
			pointY = setPointY+a*c;
			break;
		case 15:
			// Spiral logarithmic
			b = s[0]*exp(tan(s[0])*a);
			pointX = setPointX+b*cos(a);
			pointY = setPointY+b*sin(a);
			break;
		case 16:
			// Sinus overload 1
			b = setPointX/sin(setPointX/100000)/100000;
			c = sin(b*outerCycleDimension)+sin(b*innerCycleDimension)*sin(setPointX*outerCycleExtension*50);
			pointX = setPointMinX/10*(1-2*c*innerCycleExtension/5);
			pointY = setPointY*10*(1-2*sin(setPointX/100+outerCycleDimension/100));
			if (makeSound) {
				setSound[setPointStep] = int(127.5+127.5*c*0.5);
			}
			break;
		case 17:
			// Sinus overload 2
			b = setPointX/sin(setPointX/100000)/100000;
			c = sin(b*time[1])+sin(b*time[2])*sin(setPointX*time[3]*50);
			pointX = setPointMinX/100*c*time[3]/5;
			pointY = setPointY/10*sin(setPointX/100+time[1]/100);
			if (makeSound) {
				setSound[setPointStep] = int(127.5+127.5*c*0.5);
			}
			break;
	}
	switch(setGraphCeil) {
		case 0:
			// simple line
			translatePointArg = setPointX;
			translatePointSlope = 1;
			break;
		case 1:
			// trigonometric function
			b = setPointX/100+outerCycleDimension/100;
			translatePointArg = setPointMinX/10*sin(b);
			translatePointSlope = setPointMinX/10*cos(b)*1/100;
			break;
		case 2:
			// quadratic function
			b = setPointX-700;
			translatePointArg = 1/500*b*b;
			translatePointSlope = 1/500*2*b;
			break;
	}
}
