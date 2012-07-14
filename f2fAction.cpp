#include "f2fAction.h" 

void f2fAction::action()
{
	while (!stopGrid) {
		f2f_local();
		if (!stopGrid) {
			f2f_rotation();
			f2f_projection();
			zoom = 0.15;
			f2f_zoom();
			shift = new Array(1000,1000,-500);
			f2f_shift();
			
			var loop = grid_line[5];
			var min = grid_line[6];
			var max = grid_line[7];
			if (loop  == Math.round((max-min)/2)) {
				textPoint[0] = point[0];
				textPoint[1] = point[1];
			}
			
			colorZ();
			f2f_hsvToRgb();
			f2f_strokepath();
		}
	}
	if (stopGrid) {
		f2f_sound();
	}
}
