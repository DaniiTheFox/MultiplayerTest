void BON_GRAPH_FUNCTION(){
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 glMatrixMode(GL_MODELVIEW);
 glEnable(GL_CULL_FACE);
 glCullFace(GL_BACK);
 glLoadIdentity();
 cx = px+cos((angle*3.14159)/180);
 cy = py-sin((angl2*3.14159)/180);
 cz = pz-sin((angle*3.14159)/180);
 gluLookAt(px, py, pz, cx, cy, cz, 0,1,0);
 
  BON_SKY();

  Wrl_Sys.Chunk_Draw();

 glFlush();
 glutSwapBuffers();
}
