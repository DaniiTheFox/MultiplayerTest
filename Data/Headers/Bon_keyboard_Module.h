void BON_KEYBOARD_FUNCTION(unsigned char key, int x, int y){
 float tx, tz;
 switch(key){
  case '.':glutDestroyWindow(1);break;
  case 'w':
   px = cx;
   pz = cz;
  break;
  case 's':
   tx = px+cos(((angle+180)*3.14159)/180);
   tz = pz-sin(((angle+180)*3.14159)/180);
   px = tx;
   pz = tz;
  break;
  case 'a':
   tx = px+cos(((angle+90)*3.14159)/180)*0.5;
   tz = pz-sin(((angle+90)*3.14159)/180)*0.5;
   px = tx;
   pz = tz;
  break;
  case 'd':
   tx = px+cos(((angle-90)*3.14159)/180)*0.5;
   tz = pz-sin(((angle-90)*3.14159)/180)*0.5;
   px = tx;
   pz = tz;
  break;
  case ' ':
  py++;
  break;
  case 'x':
  py--;
  break;
  case 'q':
  std::cout<<"player x: "<<px<<" z:"<<pz<<std::endl;
  isDebug = true;
  break;
 }
 Wrl_Sys.Chunk_Update();
 //std::cout<<"player data: "<<pa<<" "<<px<<" "<<py<<std::endl;
}

void BON_MOUSE_FUNCTION(int x, int y){
 if(x < ((BON_SCREEN_W/2)-30)){
 angle+=2;
 if(angle < 0){
  angle = 358;
 }
 if(angle > 358){
  angle = 0;
 }
  glutWarpPointer(BON_SCREEN_W/2,240);
 }else if(x > ((BON_SCREEN_W/2)+30)){
 angle-=2;
 if(angle < 0){
  angle = 358;
 }
 if(angle > 358){
  angle = 0;
 }
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2);
 }
 if(y > (BON_SCREEN_H/2)+30){
  angl2+=2;
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2);
 }else if(y < (BON_SCREEN_H/2)-30){
  angl2-=2;
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2);
 }
}
