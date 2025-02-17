#include "../broken_texture.c"

GLuint Bon_load_bmp(char *filename, int w, int h){
 std::cout<<"loading texture"<<std::endl;
 GLuint tmp_txt;                                                           // tamaño de la textura
 unsigned char *data2;                                                          // donde se almacena el .bmp
 std::cout<<"var created"<<std::endl;
 FILE *file = fopen(filename,"rb");
 std::cout<<"loaded file"<<std::endl;
 //rewind(file);
 std::cout<<"archivo abierto..."<<std::endl;
 if(file == NULL){                                                             // si no logra descargar y leer el archivo
  std::cout<<"fallo en la lectura..."<<std::endl;
  glGenTextures(1, &tmp_txt);                                                  // inicia el modo a prueba de errores para esta textura
  glBindTexture(GL_TEXTURE_2D, tmp_txt);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);                 // genera la textura de error por defecto
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  gluBuild2DMipmaps(GL_TEXTURE_2D, brk_tex.bytes_per_pixel, brk_tex.width, brk_tex.height, GL_RGBA, GL_UNSIGNED_BYTE, brk_tex.pixel_data);
  return tmp_txt;                                                              // regresa valor de la textura al cancelar carga de archivo
 }
 std::cout<<"reescalando data..."<<std::endl;
 data2 = (unsigned char *)malloc(w*h*4);                                        // reescalar el tamaño de data a algo en lo que entre el .bmp
 std::cout<<"leyendo archivo..."<<std::endl;
 if(fread(data2, w*h*4, 1, file)){                                                  // guardar el .bmp dentro de data para su uso despues
 fclose(file);
 int index = 0;
 std::cout<<"aplicando la correccion"<<std::endl;
 for(int i = 0; i < w * h; i++){                                               // aplicar la correccion de colores al archivo
  index = i * 4;
  unsigned char R,G,B,A;
  A = data2[index];
  R = data2[index+1];
  G = data2[index+2];
  B = data2[index+3];                                                           // cuando lee el .bmp por primera vez estan invertidos R y B

  data2[index] = A;
  data2[index+1] = B;
  data2[index+2] = G;
  data2[index+3] = R;                                                          // esto aplica una correccion colocando todo en su sitio respectivo
 }
 std::cout<<"correccion aplicada generando..."<<std::endl;
 glGenTextures(1, &tmp_txt);
 glBindTexture(GL_TEXTURE_2D, tmp_txt);
 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);                 // si hubo lectura genera la textura desde .bmp
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data2);
 free(data2);
 }else{                                                                        // libera la memoria de data ya no usada
  //load_bmp_texture(filename);
  std::cout<<"fallo en la lectura..."<<std::endl;
  glGenTextures(1, &tmp_txt);                                                  // inicia el modo a prueba de errores para esta textura
  glBindTexture(GL_TEXTURE_2D, tmp_txt);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);                 // genera la textura de error por defecto
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  gluBuild2DMipmaps(GL_TEXTURE_2D, brk_tex.bytes_per_pixel, brk_tex.width, brk_tex.height, GL_RGBA, GL_UNSIGNED_BYTE, brk_tex.pixel_data);
 }
 return tmp_txt;
}


void BON_IDLE_FUNCTION(){
  usleep(33);
  glutPostRedisplay();
}

void mcFog(float strt , float end ,float dens){
 GLuint filter;
 GLfloat FogColor[4] = {0.8,0.8,1.0,1.0};
 glClearColor(0.8,0.8,1.0,0);
 glFogi(GL_FOG_MODE , GL_LINEAR);
 glFogfv(GL_FOG_COLOR , FogColor);
 glFogf(GL_FOG_DENSITY , dens );
 glHint(GL_FOG_HINT , GL_DONT_CARE);
 glFogf(GL_FOG_START , strt );
 glFogf(GL_FOG_END , end);
 //glEnable(GL_FOG);
}

void BON_SKY(){
 glDisable(GL_FOG);
 glPushMatrix();
  glTranslatef(px,0,pz);
  glBindTexture(GL_TEXTURE_2D, SKY_TEXTURE);
  glBegin(GL_QUADS);
   glTexCoord2d(  0.0+xoff,  0.0);glVertex3f( 500, 255,  500);
   glTexCoord2d(  0.0+xoff,500.0);glVertex3f(-500, 255,  500);
   glTexCoord2d(500.0+xoff,500.0);glVertex3f(-500, 255, -500);
   glTexCoord2d(500.0+xoff,  0.0);glVertex3f( 500, 255, -500);
  glEnd();
 glPopMatrix();
 //glEnable(GL_FOG);
 glPushMatrix();
  glTranslatef(px,0,pz);
  glBindTexture(GL_TEXTURE_2D, WATER_TEXTURE);
  glBegin(GL_QUADS);
   glTexCoord2d(  0.0+xoff,   0.0);glVertex3f(-500, -25,  500);
   glTexCoord2d(  0.0+xoff, 500.0);glVertex3f( 500, -25,  500);
   glTexCoord2d(500.0+xoff, 500.0);glVertex3f( 500, -25, -500);
   glTexCoord2d(500.0+xoff,   0.0);glVertex3f(-500, -25, -500);
  glEnd();
 glPopMatrix();
 glEnable(GL_FOG);
}

void glIni(){
 glClearColor(0,0,0,0);
 glEnable(GL_TEXTURE_2D);
 glEnable(GL_BLEND);
 glEnable(GL_DEPTH_TEST);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(60,1,1,1000);
 mcFog(13,20,10);
 GRASS_TEXTURE = Bon_load_bmp( "Data/Textures/grass.bmp",16,48);
 STONE_TEXTURE = Bon_load_bmp( "Data/Textures/stone.bmp",16,48);
 WATER_TEXTURE = Bon_load_bmp( "Data/Textures/water.bmp",64,64);
 SKY_TEXTURE   = Bon_load_bmp("Data/Textures/clouds.bmp",64,64);
}

