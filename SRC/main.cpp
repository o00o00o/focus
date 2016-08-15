#include "isolation.h"
#include "timer.h"
#include "helper.h"

int main( int argc, char* args[] ) {
  //start up SDL
  if ( !init() ) {
    printf( "Failed to initialize.\n" );
  }
  else {
    //load media
    if ( !load_media() ) {
      printf( "Failed to load media.\n" );
    }
    else{
      //main loop flag
      bool quit = false;
      bool on_break = false;
      bool is_short_break = true;

      //event handler
      SDL_Event e;

      //setup colors for text;
      SDL_Color white = { 255, 255, 255, 255 };
      SDL_Color black = { 0, 0, 0, 255 };


      timer_texture.set_blend_mode( SDL_BLENDMODE_BLEND );

      //timer for break;
      Timer timer;

      //stopwatch for extra study time;
      Timer stopwatch;

      //coeffince for finding alpha
      double coefficient = get_coefficient( 10 );

      //In memory text stream
      std::stringstream time_text;

      //while running
      while ( !quit ) {
        //handle events on queue
        while ( SDL_PollEvent( &e ) != 0 ) {
          //user quit
          if ( e.type == SDL_QUIT ) {
            quit = true;
          }
          else if ( e.type == SDL_USEREVENT ) {
            //the call back function event
            //TODO: get_alpha && check to see if its the last time and thus remove the timer
          }
          else if ( e.type == SDL_KEYDOWN ) {
            switch ( e.key.keysym.sym ) {
              case SDLK_q: {//quit on q
                quit = true;
                break;
              }

              case SDLK_SPACE: { //start timer on space
                if ( on_break ) {
                  on_break = end_break();
                }
                else {
                  on_break = start_break( is_short_break );
                  timer.start_countdown( 5 );
                }

                //SDL_TimerID count_down = SDL_AddTimer( 3000 , count_down_callback, NULL); //start a timer for a mintue

                break;
              }

              case SDLK_s: {
                timer.start_stopwatch();
                break;
              }

              case SDLK_f: {//toggle fullscreen on f
                if ( !full_screen ) {
                  SDL_SetWindowFullscreen( g_window, SDL_WINDOW_FULLSCREEN_DESKTOP );
                  full_screen = true;
                }
                else if ( full_screen ) {
                    SDL_SetWindowFullscreen( g_window, 0 );
                    full_screen = false;
                }
                break;
              }
            }
          }
        }

        //Set text to be rendered 
        time_text.str( "" );
        time_text << "Seconds since start time " << ( timer.get_countdown() );

        //Render text
        if( !timer_texture.load_from_rendered_text( time_text.str().c_str(), white, open_sans ) )
        {
          printf( "Unable to render time texture!\n" );
        }
        //render outline text
        if( !timer_outline_texture.load_from_rendered_text( time_text.str().c_str(), black, open_sans_outline ) )
        {
          printf( "Unable to render time texture!\n" );
        }

        render_screen();
      }
    }
  }

  //free memory and close SDL
  close();

  return 0;
}
