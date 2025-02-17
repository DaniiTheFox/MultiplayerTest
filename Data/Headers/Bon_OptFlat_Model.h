class Bon_Flat{
 private:
  float x,y,z;
  float rh,rv;
  float scala;
 public:
  Flat_v(float _x, float _y, float _z, float _scala);
  void DrawFlatLookAt(float lx,float ly,float lz);
};

Flat_v::Flat_v(float _x, float _y, float _z, float _scala){
 x = _x;
 y = _y;
 z = _z;
 scala = _scala;
}

void Flat_v::DrawFlatLookAt(float lx,float ly,float lz, float sx1, float sx2){
 float tmpa = ((atan2((lx-x),(lz-z))*180)/3.14159);
 if(tmpa < 0){
  tmpa += 360;
 }
 //std::cout<<tmpa<<"\n";
 float tmya = 0;
 glPushMatrix();
  glTranslatef(x,y,z);
  glRotatef(tmpa,tmya,tmpa,1);
  glBegin(GL_QUADS);
  glTexCoord2d(sx1,0);
  glVertex3f(-scala/2,-scala,0);
  glTexCoord2d(sx1,-1);
  glVertex3f(-scala/2, scala,0);
  glTexCoord2d(sx2,-1);
  glVertex3f( scala/2, scala,0);
  glTexCoord2d(sx2,0);
  glVertex3f( scala/2,-scala,0);
  glEnd();
 glPopMatrix();
}
