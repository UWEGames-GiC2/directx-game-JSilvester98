#ifndef _STAR_H_
#define _STAR_H_
#include "CMOGO.h"


//=================================================================
//Terrian Game Object Class (i.e. an Object that just sits there)
//=================================================================

struct GameData;

class Star : public CMOGO
{
public:
	Star(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll, Vector3 _scale);
	~Star();



	virtual void Tick(GameData* _GD) override;

protected:

};

#endif