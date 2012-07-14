class f2f3D
{
	
	public:

		double shiftX, shiftY, shiftZ;
		void fShift();
		
		double zoomX, zoomY, zoomZ;
		void fZoom();
		
		double projectionAngelX, projectionAngelY, projectionAngelZ;
		double projectionCameraX, projectionCameraY, projectionCameraZ;
		double projectionViewerX, projectionViewerY, projectionViewerZ;
		bool projectionNewAngel;
		void fProjection();
		
		double rotationPoint1X, rotationPoint1Y, rotationPoint1Z;
		double rotationPoint2X, rotationPoint2Y, rotationPoint2Z;
		double rotationAngel;
		bool rotationNewAxis, rotationNewAngel;
		void fRotation();
		
		double translatePointArg, translatePointSlope;
		void fTranslate();
		
		double centralAxisX, centralAxisY, centralCenterX, centralCenterY, centralMoveX, centralMoveY;
		bool centralTriggerCenter, centralTriggerAxis;
		void fCentral();
		
		double planePoint1X, planePoint1Y, planePoint1Z;
		double planePoint2X, planePoint2Y, planePoint2Z;
		double planePoint3X, planePoint3Y, planePoint3Z;
		double planeRotateAngel;
		bool planeNewPlane, planeRotatePlane;
		void fPlane();

		double outerCycleDimension, outerCycleExtension, innerCycleDimension, innerCycleExtension;
		bool setNewControl;
		double setPointX, setPointMinX, setPointY, setPointStep;
		int setGraph, setGraphCeil; 
		void fSet();
};

