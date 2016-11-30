class HitBox{
public:
	HitBox(float x, float y,float z, float length);	//constructor

	void hello();		//hello function
	float getX();
	float getY();
	float getZ();
	float getLength();
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float x,y,z;
	float length;

private:
	float privateVar;
};
