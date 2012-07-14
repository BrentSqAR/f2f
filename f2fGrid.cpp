#include "f2fGrid.h"

void f2fGrid::fParse() {	
	if (gridLineOrder == 1) {
		setPointX = -(gridLineStartX+gridLineStep);
	} else {
		setPointX = gridLineStartX+gridLineStep;
	}
	setPointMinX = gridLineStartX;
	setPointY = gridLineY;
	setPointStep = gridLineStep;
	setGraphCeil = 1;
	fSet();
	if (gridLineOrder == 1) {
		swap = pointX;
		pointX = pointY;
		pointY = -swap;
	}
	fTranslate();	
	if (gridLineOrder == 1) {
		setPointX = -pointY;
	} else {
		setPointX = pointX;
	}
	setGraphCeil = 2;
	fSet();
	if (gridLineOrder == 1) {
		swap = pointX;
		pointX = pointY;
		pointY = -swap;
	}
	fTranslate();	
	fCentral();
}

void f2fGrid::fInitStep() {
	gridLineY = gridMinX;
	xGrid = false;
	yGrid = false;
	stopGrid = false;
}

void f2fGrid::fStep() {
	if (!xGrid) {
		if (gridLineY == gridMinX) {
			gridLineStartX = gridMinY;
			gridLineStopX = gridMaxY;
			gridLineStep = 0;
			gridLineOrder = 1;
		} else if (!(gridLineY == gridMinX) && ((gridLineY+gridDeltaX) <= gridMaxX)) {
			gridLineY += gridDeltaX;
			gridLineStep = 0;
		} else {
			xGrid = true;
			gridLineY = gridMinY;
		}
	}
	if (xGrid && !yGrid) {
		if (gridLineY == gridMinY) {
			gridLineStartX = gridMinX;
			gridLineStopX = gridMaxX;
			gridLineStep = 0;
			gridLineOrder = 2;
		} else if (!(gridLineY == gridMinY) && ((gridLineY+gridDeltaY) <= gridMaxY)) {
			gridLineY += gridDeltaY;
			gridLineStep = 0;
		} else {
			yGrid = true;
		}	
	}
	if (xGrid && yGrid) {
		stopGrid = true;
	}
}

void f2fGrid::fInitLocal() {
	nextGridLine = true;
	strokeLine = false;
}

void f2fGrid::fLocal() {	
	if (nextGridLine) {
		fStep();
		nextGridLine = false;
		if (makeSound) {
			soundSampleMax = int(gridLineStopX-gridLineStartX)+1;
			if (soundSampleMax < 1) {soundSampleMax = 1;}
			setSound = new int[soundSampleMax];
		}
	}
	if (!nextGridLine && !stopGrid) {			
		if (gridLineStep <= (gridLineStopX-gridLineStartX)) {	
			fParse();		
			++gridLineStep;
		} else {
			nextGridLine = true;
			strokeLine = true;
		}
	}
}
