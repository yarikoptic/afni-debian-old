#include "niml.h"

/*--- Debug printout of a NIML element. ---*/

void NIML_to_terminal( void *nini, int mode, int do_stderr)
{
   NI_stream ns_err ;
   if (do_stderr) ns_err = NI_stream_open( "stderr:" , "w" ) ;
   else ns_err = NI_stream_open( "stdout:" , "w" ) ;
   if( ns_err != NULL ){
     NI_write_element( ns_err , nini , mode ) ;
     NI_stream_close( ns_err ) ;
   }
}

/*--- Open a NIML stream, read elements from it, print them ---*/

int main( int argc , char *argv[] )
{
   NI_stream ns ;
   void *nini = NULL, *vel=NULL;
   char *strm=NULL;
   int nn, mode = NI_TEXT_MODE;
   int dodup = 0, nodata=0, dostderr=1;
   
   if( argc < 2 || !strcmp(argv[1], "-help") || !strcmp(argv[1], "-h")){
      fprintf(stderr,
              "\n"
              "   Usage: niccc [-dup] [-nodata] streamspec\n"
              "\n"
              "A program for conducting certain NIML tests \n"
              "on input from streamspec and write the results to stderr\n"
              "\n"
              "Example:\n"
              "    niccc file:Something.niml \n"
              "\n"
              "Mandatory arguments:\n"
              "   streamspec: A string defining a NIML stream.\n"
              "\n"
              "Options:\n"
              "   -dup: Duplicate the element before showing it.\n"
              "         This is to test NI_duplicate function.\n"
              "   -nodata: Show header parts only in output\n"
              "   -stdout: write elements to stdout, instead of stderr\n"
              "\n");
      exit(0);
   }
   nn = 1;
   while (nn < argc && argv[nn][0] == '-') {
      if (!strcmp(argv[nn],"-dup")) {
         dodup = 1; ++nn; continue;
            }
      if (!strcmp(argv[nn],"-nodata")) {
         nodata = 0; ++nn; continue;
      }
      if (!strcmp(argv[nn],"-stdout")) {
         dostderr = 0; ++nn; continue;
      }
      fprintf(stderr,
               "Bad option %s. See niccc -help for details.\n", 
               argv[nn]);
      exit(1);
   }
   if (nodata) mode = mode&NI_HEADERONLY_FLAG;
   
   if (nn >= argc) {
      fprintf(stderr,"Usage: niccc [-dup] streamspec\n");exit(1);
   }
   strm = argv[nn];
   ns = NI_stream_open( strm, "r" ) ;
   if( ns == NULL ){
      fprintf(stderr,"*** niccc: NI_stream_open fails\n") ; exit(1) ;
   }
   /*** NI_stream_setbufsize( ns , 6666 ) ; ***/
   while(1){
     nn = NI_stream_goodcheck( ns , 1 ) ;
     if( nn < 0 ){
       if (strncmp(strm,"file:",5)) {
         fprintf(stderr,"\n*** niccc: Stream fails\n"); exit(1);
       } else {
         exit(1);
       }
     }
     if( nn == 0 ){ NI_sleep(5); continue; }  /* waiting for Godot */

     nn = NI_stream_readcheck( ns , 1 ) ;     /* check for data */

     if( nn > 0 ){
       nini = NI_read_element( ns , 2 ) ;
       if( nini == NULL ){
         fprintf(stderr,"*** niccc: read returns NULL\n");
       } else {
         if (dodup) {
            fprintf(stderr,"*** niccc: duplicated returned element:\n");
            vel = NI_duplicate(nini, 1);
            NI_free_element( nini ) ; nini=NULL;
            NIML_to_terminal( vel, mode, dostderr ) ;
         } else {
           fprintf(stderr,"*** niccc: read returned an element:\n") ;
            NIML_to_terminal( nini, mode, dostderr ) ;
         }
         if (nini) NI_free_element( nini ) ; nini=NULL;
         if (vel) NI_free_element( vel ); vel = NULL;
       }
     }
   }
}
