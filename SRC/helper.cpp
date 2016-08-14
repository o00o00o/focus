#include "isolation.h"
#include <cmath>

//find the coefficient using the user set timer mintues
double get_coefficient( int total_minutes ) {
  double coefficient = 0.0;
  coefficient = 255 / pow( (double)total_minutes, 2.0 );
  return coefficient;
}

//find alpha value at specific mintues using coefficient
Uint8 get_alpha( int minutes, double coefficient ) {
  Uint8 alpha = 0;
  alpha = ceil( coefficient * pow( minutes, 2 ) );
  if ( alpha <= 255 ) {
    return alpha;   //make sure that alpha is 255 or lower
  }
  else {
    return alpha = 255;
  }
}

//start the break, TODO:release keyboard and mouse control;
bool start_break( bool short_break ) {
  if ( full_screen ){
    SDL_SetWindowFullscreen( g_window, 0 );     //go into windowed mode
    full_screen = false;

    if( !background_texture.load_from_file( "img/vancouver_1280.jpg" ) ) {    //load windowed background
      printf( "Failed to load background texture 1280!\n" );
    }
    else {
      printf("hello\n" );
      if ( short_break ) {
        background_texture.render( 0, 0 );
        text_overlay.load_from_file( "img/shortbreak_1920.png" );    //load windowed overlay short;
      }
      else if ( !short_break ) {
        text_overlay.load_from_file( "img/longbreak_1920.png" );     //load windowed overlay long;
      }
    }
  }
  //TODO: render function
  background_texture.render( 0, 0 );
  text_overlay.render( 0, 0 );
  return true;
}


bool end_break() {
  //Todo: end the break restart everything
  //SDL_TimerID count_down = SDL_AddTimer( 3000 , count_down_callback, NULL); //start a timer for a mintue
  //return false;
}


//call backfunction for timer, pushing ONE_MINUTE into event queue
//also cause callback to be called again at one mintue
Uint32 count_down_callback( Uint32 interval, void *param ) {
  SDL_Event event;
  SDL_UserEvent userevent;

  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  userevent.data1 = NULL;
  userevent.data2 = NULL;

  event.type = SDL_USEREVENT;
  event.user = userevent;

  SDL_PushEvent(&event);
  return(interval);
}
