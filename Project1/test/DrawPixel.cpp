#include "DxLib.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);

	if( DxLib_Init() == -1 )
	{
		return -1;
	}

	char key[256];
	int gh[12];
	int x=300, y=240;

	LoadDivGraph("img/charall.png", 12, 3, 4, 49, 66, gh);

	SetDrawScreen(DX_SCREEN_BACK);

	float move=1.0f;
	int xcount=0, ycount=0;
	int ix=0, iy=0, result=0;

	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && GetHitKeyStateAll(key)==0) {

		if(key[KEY_INPUT_LEFT]==1 || key[KEY_INPUT_RIGHT]==1) {
			if(key[KEY_INPUT_UP]==1 || key[KEY_INPUT_DOWN]==1) {
				move=0.71f;
			} else {
				move=1.0f;
			}
		} else if(key[KEY_INPUT_UP]==1 || key[KEY_INPUT_DOWN]==1) {
			move=1.0f;
		}

		if(key[KEY_INPUT_LEFT]==1) {
			x-=(int)4*move;
		}

		if(key[KEY_INPUT_RIGHT]==1) {
			x+=(int)4*move;
		}

		if(key[KEY_INPUT_UP]==1) {
			y-=(int)4*move;
		}

		if(key[KEY_INPUT_DOWN]==1) {
			y+=(int)4*move;
		}

		//

		if(key[KEY_INPUT_LEFT]==1) {
			if(xcount>0) xcount=0;
			--xcount;
		}

		if(key[KEY_INPUT_RIGHT]==1) {
			if(xcount<0) xcount=0;
			++xcount;
		}

		if(key[KEY_INPUT_UP]==1) {
			if(ycount>0) ycount=0;
			--ycount;
		}

		if(key[KEY_INPUT_DOWN]==1) {
			if(ycount<0) ycount=0;
			++ycount;
		}

		//

		ix=abs(xcount)%30/10;
		iy=abs(ycount)%30/10;

		//

		if(xcount>0) {
			ix+=3;
			result=ix;
		} else if(xcount<0) {
			ix+=9;
			result=ix;
		}

		if(ycount>0) {
			iy+=6;
			result=iy;
		} else if(ycount<0) {
			iy+=0;
			result=iy;
		}

		if(move==0.71f) result=ix;

		//

		DrawGraph(x, y, gh[result], TRUE);

		//

		if(key[KEY_INPUT_LEFT]!=1 && key[KEY_INPUT_RIGHT]!=1) {
			xcount=0;
		}

		if(key[KEY_INPUT_UP]!=1 && key[KEY_INPUT_DOWN]!=1) {
			ycount=0;
		}

		//

		if(key[KEY_INPUT_ESCAPE]==1) {
			break;
		}
	}

	DxLib_End();

	return 0;
}
