class f2fGrid
{	
		bool xGrid, yGrid, nextGridLine;

	public:
		bool stopGrid, strokeLine;
		
		double gridMinX;
		double gridMinY;
		double gridMaxX;
		double gridMaxY;
		double gridDeltaX;
		double gridDeltaY;
		
		double gridLineStartX;
		double gridLineStopX;
		double gridLineY;
		int gridLineStep;
		int gridLineOrder;
		
		bool makeSound;
		int soundSampleMax;
		int *setSound;
		
		void fParse();
		void fInitStep();		
		void fStep();
		void fInitLocal();		
		void fLocal();
};
