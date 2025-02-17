void Bon_draw_cube(int map[16][255][16],int _px,int _py,int _pz,int ax, int ay, int az,float s){
       //std::cout<<"data:"<<map[0][0][0]<<std::endl;
       glTranslatef(ax,ay,az);
	glBegin(GL_QUADS); 
	if((_px)<16  && (_px)>0){
	if((_py)<255 && (_py)>0){
	if((_pz)<16  && (_pz)>0){
	if(map[_px][_py+1][_pz] == 0){
  	 glTexCoord2d(0.0+xoff,0.6666);glVertex3f( s, s,-s);
     	 glTexCoord2d(0.0+xoff,1.0);glVertex3f(-s, s,-s);
     	 glTexCoord2d(1.0+xoff,1.0);glVertex3f(-s, s, s);
     	 glTexCoord2d(1.0+xoff,0.6666);glVertex3f( s, s, s);
	}
	if(map[_px][_py-1][_pz] == 0){
     	 glTexCoord2d(0.0+xoff,0.0);glVertex3f( s, -s,  s);
     	 glTexCoord2d(0.0+xoff,0.3333);glVertex3f(-s, -s,  s);
     	 glTexCoord2d(1.0+xoff,0.3333);glVertex3f(-s, -s, -s);
     	 glTexCoord2d(1.0+xoff,0.0);glVertex3f( s, -s, -s);
	}
        if(map[_px][_py][_pz+1] == 0){
	 glTexCoord2d(0.0+xoff,0.6866);glVertex3f( s,  s, s);
     	 glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, s);
     	 glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, s);
     	 glTexCoord2d(0.0+xoff,0.3533);glVertex3f( s, -s, s);
        }
	if(map[_px][_py][_pz-1] == 0){
     	 glTexCoord2d(0.0+xoff,0.3533);glVertex3f( s, -s, -s);
     	 glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, -s);
     	 glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, -s);
     	 glTexCoord2d(0.0+xoff,0.6866);glVertex3f( s,  s, -s);
	}
	if(map[_px-1][_py][_pz] == 0){
     	 glTexCoord2d(0.0+xoff,0.6866);glVertex3f(-s,  s,  s);
     	 glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, -s);
     	 glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, -s);
     	 glTexCoord2d(0.0+xoff,0.3533);glVertex3f(-s, -s,  s);
	}
	if(map[_px+1][_py][_pz] == 0){
     	 glTexCoord2d(0.0+xoff,0.6866);glVertex3f(s,  s, -s);
     	 glTexCoord2d(1.0+xoff,0.6866);glVertex3f(s,  s,  s);
     	 glTexCoord2d(1.0+xoff,0.3533);glVertex3f(s, -s,  s);
     	 glTexCoord2d(0.0+xoff,0.3533);glVertex3f(s, -s, -s);
 	}
        }}}
   glEnd();
}
