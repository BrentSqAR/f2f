#include "f2fDraw.h" 

void f2fDraw::fGetArea() {
	bool areaFlag = false;
	bool p1In, p2In;
	int	hit = 0;
	double dx, dy, sx, sy, a, b, m, d1, d2, d3;
	double pointCut[6], pointArea[6];

	if (!((isinf(pointX) && isinf(pointPrevY)) || (isinf(pointY) && isinf(pointPrevX)))) {
		p1In = ((!(pointPrevX < areaXMin) && !(pointPrevX > areaXMax)) && (!(pointPrevY < areaYMin) && !(pointPrevY > areaYMax))) ? true : false;
		p2In = ((!(pointX < areaXMin) && !(pointX > areaXMax)) && (!(pointY < areaYMin) && !(pointY > areaYMax))) ? true : false;
		if (!(p1In && p2In)) {
			dx = pointX-pointPrevX;
			dy = pointY-pointPrevY;
			a = dy/dx;
			if (isnan(a)) {
				if ((fabs(dx) < 0.00001) && !(fabs(dy)) < 0.00001) {
					a = INFINITY;
				} else if (isinf(dx)) {
					a = 1;
				}
			}
			b = pointPrevY-pointPrevX*a;
			if (!(isnan(a))) {
				if (((pointX <= areaXMin) && (areaXMin <= pointPrevX)) || ((pointPrevX <= areaXMin) && (areaXMin <= pointX))) {
					pointCut[0] = areaXMin;
					if (isnan(b)) {
						m = (areaXMax+areaXMin)*0.5;
						d1 = fabs(m-pointX);
						d2 = fabs(m-pointPrevX);
						d3 = d1/(d1+d2);
						if (isnan(d3)) {
							if (isinf(d1) && !isinf(d2)) {
								d3 = 1;
							} else if (isinf(d2) && !isinf(d1)) {
								d3 = 0;
							} else {
								d3 = 0.5;
							}
						}
						pointCut[1] = d3*(pointPrevY-pointY)+pointY;
					} else {
						pointCut[1] = a*areaXMin+b;
					}
					hit = ((areaYMin <= pointCut[1]) && (pointCut[1] < areaYMax)) ? 1 : 0;
				}
				if (((pointY <= areaYMin) && (areaYMin <= pointPrevY)) || ((pointPrevY <= areaYMin) && (areaYMin <= pointY))) {
					pointCut[hit*3] = (isinf(a)) ? pointX : ((areaYMin-b)/a);
					pointCut[hit*3+1] = areaYMin;
					hit = ((areaXMin < pointCut[hit*3]) && (pointCut[hit*3] <= areaXMax)) ? ++hit : hit;
				}
				if (((pointX <= areaXMax) && (areaXMax <= pointPrevX)) || ((pointPrevX <= areaXMax) && (areaXMax <= pointX))) {
					pointCut[hit*3] = areaXMax;
					if (isnan(b)) {
						m = (areaXMax+areaXMin)*0.5;
						d1 = fabs(m-pointX);
						d2 = fabs(m-pointPrevX);
						d3 = d1/(d1+d2);
						if (isnan(d3)) {
							if (isinf(d1) && !isinf(d2)) {
								d3 = 1;
							} else if (isinf(d2) && !isinf(d1)) {
								d3 = 0;
							} else {
								d3 = 0.5;
							}
						}
						pointCut[hit*3+1] = d3*(pointPrevY-pointY)+pointY;
					} else {
						pointCut[hit*3+1] = a*areaXMax+b;
					}
					hit = ((areaYMin <= pointCut[hit*3+1]) && (pointCut[hit*3+1] < areaYMax)) ? ++hit : hit;
				}
				if (((pointY <= areaYMax) && (areaYMax <= pointPrevY)) || ((pointPrevY <= areaYMax) && (areaYMax <= pointY))) {
					pointCut[hit*3] = (isinf(a)) ? pointX : ((areaYMax-b)/a);
					pointCut[hit*3+1] = areaYMax;
					hit = ((areaXMin < pointCut[hit*3]) && (pointCut[hit*3] <= areaXMax)) ? ++hit : hit;
				}
				if (hit == 2) {
					sx = pointCut[3]-pointCut[0];
					sy = pointCut[4]-pointCut[1];
					if ((((sx < 0) && (dx > 0)) || ((sx > 0) && (dx < 0))) || (((sy < 0) && (dy > 0)) || ((sy > 0) && (dy < 0)))) {
						pointArea[0] = pointCut[3];
						pointArea[1] = pointCut[4];
						pointArea[3] = pointCut[0];
						pointArea[4] = pointCut[1];
					} else {
						pointArea[0] = pointCut[0];
						pointArea[1] = pointCut[1];
						pointArea[3] = pointCut[3];
						pointArea[4] = pointCut[4];
					}
					areaFlag = true;
				}
				if (hit == 1) {
					if (p1In) {
						pointArea[0] = pointPrevX;
						pointArea[1] = pointPrevY;
						pointArea[3] = pointCut[0];
						pointArea[4] = pointCut[1];
						areaFlag = true;
					}
					if (p2In) {
						pointArea[0] = pointCut[0];
						pointArea[1] = pointCut[1];
						pointArea[3] = pointX;
						pointArea[4] = pointY;
						areaFlag = true;
					}
				}
			}
		}
		if (p1In && p2In) {
			pointArea[0] = pointPrevX;
			pointArea[1] = pointPrevY;
			pointArea[3] = pointX;
			pointArea[4] = pointY;
			areaFlag = ((fabs(pointX-pointPrevX) < 0.00001) && (fabs(pointY-pointPrevY) < 0.00001)) ? false : true;
		}
	}
}

void f2fDraw::strokepath()
{ 
}
