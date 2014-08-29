#include "SUMA_suma.h"

int SUMA_ProcessCommand(char *com, SUMA_COMM_STRUCT *cs, char *EchoNel)
{
   static char FuncName[]={"SUMA_ProcessCommand"};
   int i, suc;
   float *far=NULL;
   char *act, *pos, *stp;
   NI_group *ngr = NULL;
   SUMA_SurfaceObject *SO=NULL;
   SUMA_SO_File_Type tp = SUMA_FT_NOT_SPECIFIED;
   SUMA_Boolean ans = NOPE;
   SUMA_Boolean LocalHead = NOPE;
   
   SUMA_ENTRY;
   
   if (!com) { SUMA_S_Err("NULL command"); SUMA_RETURN(NOPE); }
   SUMA_LHv("Called with %s\n", com);
   SUMA_GET_BETWEEN_BLANKS(com, NULL, pos);
   act = NULL;
   SUMA_COPY_TO_STRING(com, pos, act); com = pos;
   if (!act) { SUMA_S_Err("No action found"); SUMA_RETURN(NOPE); }
   
   ans = YUP;
   SUMA_TO_LOWER(act);
   if (strcmp((act), "show_surf") == 0) {
      SO = SUMA_ShowSurfComToSO(com);
      SUMA_LHv("Sending Surface %s\n", SO->Label); /* send the surface */
      SUMA_SendSumaNewSurface(SO, cs);
      if (EchoNel) 
         SUMA_S_Warn("Sorry, no echo for show_surf. Complain to author.");
   } else if (strcmp((act), "node_xyz") == 0) {
      SO = SUMA_NodeXYZComToSO(com);
      SUMA_LHv("Sending XYZ to %s", SO->Label);
      if (!SUMA_SendToSuma (SO, cs, (void *)SO->NodeList, SUMA_NODE_XYZ, 1)){
         SUMA_SL_Warn("Failed in SUMA_SendToSuma\nCommunication halted.");
      }
      if (EchoNel) 
         SUMA_S_Warn("Sorry, no echo for node_xyz. Complain to author.");
   } else if (strcmp((act), "load_dset") == 0) {
      if (!(ngr = SUMA_ComToNgr(com, act))) {
         SUMA_S_Err("Failed to process command."); SUMA_RETURN(NOPE); 
      }
      SUMA_LH("Sending LoadDset to suma");
      if (!SUMA_SendToSuma (SO, cs, (void *)ngr,SUMA_ENGINE_INSTRUCTION, 1)){
         SUMA_SL_Warn("Failed in SUMA_SendToSuma\nCommunication halted.");
      }
      if (EchoNel) NEL_WRITE_TX(ngr, EchoNel, suc);
      NI_free_element(ngr); ngr = NULL;
   } else if (strcmp((act), "load_col") == 0) {
      if (!(ngr = SUMA_ComToNgr(com, act))) {
         SUMA_S_Err("Failed to process command."); SUMA_RETURN(NOPE); 
      }
      SUMA_LH("Sending LoadCol to suma");
      if (!SUMA_SendToSuma (SO, cs, (void *)ngr,SUMA_ENGINE_INSTRUCTION, 1)){
         SUMA_SL_Warn("Failed in SUMA_SendToSuma\nCommunication halted.");
      }
      if (EchoNel) NEL_WRITE_TX(ngr, EchoNel, suc);
      NI_free_element(ngr); ngr = NULL;
   }else if (strcmp((act), "surf_cont") == 0) {
      if (!(ngr = SUMA_ComToNgr(com, act))) {
         SUMA_S_Err("Failed to process command."); SUMA_RETURN(NOPE); 
      }
      SUMA_LH("Sending SetSurfCont to suma");
      if (!SUMA_SendToSuma (SO, cs, (void *)ngr,SUMA_ENGINE_INSTRUCTION, 1)){
         SUMA_SL_Warn("Failed in SUMA_SendToSuma\nCommunication halted.");
      }
      if (EchoNel) NEL_WRITE_TX(ngr, EchoNel, suc);
      NI_free_element(ngr); ngr = NULL; 
   } else if (strcmp((act), "viewer_cont") == 0) {
      if (!(ngr = SUMA_ComToNgr(com, act))) {
         SUMA_S_Err("Failed to process command."); SUMA_RETURN(NOPE); 
      }
      SUMA_LH("Sending SetViewerCont to suma");
      if (!SUMA_SendToSuma (SO, cs, (void *)ngr,SUMA_ENGINE_INSTRUCTION, 1)){
         SUMA_SL_Warn("Failed in SUMA_SendToSuma\nCommunication halted.");
      }
      if (EchoNel) NEL_WRITE_TX(ngr, EchoNel, suc);      
      NI_free_element(ngr); ngr = NULL;
   } else if (strcmp((act), "recorder_cont") == 0) {
      if (!(ngr = SUMA_ComToNgr(com, act))) {
         SUMA_S_Err("Failed to process command."); SUMA_RETURN(NOPE); 
      }
      SUMA_LH("Sending SetRecorderCont to suma");
      if (!SUMA_SendToSuma (SO, cs, (void *)ngr,SUMA_ENGINE_INSTRUCTION, 1)){
         SUMA_SL_Warn("Failed in SUMA_SendToSuma\nCommunication halted.");
      }
      if (EchoNel) NEL_WRITE_TX(ngr, EchoNel, suc);
      NI_free_element(ngr); ngr = NULL;
   } else if (strcmp((act), "sleep") == 0) {
      double slp;
      char **argt=NULL;
      int argtc = 0;

      /* change com to a bunch of arguments */
      argt = SUMA_com2argv(com, &argtc); 

      if (argtc != 2) {
         SUMA_S_Errv("Expecting one value after sleep, have %d\n%s\n", 
                        argtc-1, argt[1]);
         ans = NOPE;
      }
      slp = SUMA_ParseTime(argt[1]);
      SUMA_S_Notev("Sleeping for %.3lf seconds\n", slp/1000.0);
      NI_sleep((int)slp);
      argt = SUMA_free_com_argv(argt, &argtc);
   } else if (strcmp((act), "pause") == 0) {
      char **argt=NULL, *msg=NULL;
      int argtc = 0;
      /* change com to a bunch of arguments */
      argt = SUMA_com2argv(com, &argtc); 
      if (argtc < 2) {
         SUMA_PAUSE_PROMPT("Pausing DriveSuma.\nDo something to proceed.\n");
      } else {
        for (i=1; i<argtc; ++i) 
            msg = SUMA_append_replace_string(msg, argt[i], " ", 1);
        SUMA_PAUSE_PROMPT(msg);
      }
      if (msg) SUMA_free(msg); msg = NULL;
      argt = SUMA_free_com_argv(argt, &argtc);
   } else if (strcmp((act), "kill_suma") == 0) {
      if (!(ngr = SUMA_ComToNgr(com, act))) {
         SUMA_S_Err("Failed to process command."); SUMA_RETURN(NOPE); 
      }
      SUMA_LH("Sending kill_suma to suma");
      if (!SUMA_SendToSuma (SO, cs, (void *)ngr,SUMA_ENGINE_INSTRUCTION, 1)){
         SUMA_SL_Warn("Failed in SUMA_SendToSuma\nCommunication halted.");
      }
      if (EchoNel) NEL_WRITE_TX(ngr, EchoNel, suc);
      
      if (1) {
         /* go bad anyway without waiting for stream to go bad 
         because suma will be dying. No point in waiting if
         if there was a communication error. 
               Added per Yaroslav Halchenko's request     Sept 2013 */
         cs->GoneBad = YUP;
      } else {
         SUMA_Wait_Till_Stream_Goes_Bad(cs, 100, 1000, 0);
      }
      NI_free_element(ngr); ngr = NULL;
      ans = -1; 
   } else {
      fprintf(SUMA_STDERR, 
               "Error %s: Action '%s' not supported.\n", FuncName, act);
      ans = NOPE;
   }
   
   if (SO) SUMA_Free_Surface_Object(SO); SO = NULL;
   if (act) SUMA_free(act);
   SUMA_RETURN(ans);
}

SUMA_GENERIC_PROG_OPTIONS_STRUCT *SUMA_DriveSuma_ParseInput(
                  char *argv[], int argc, SUMA_GENERIC_ARGV_PARSE *ps)
{
   static char FuncName[]={"SUMA_DriveSuma_ParseInput"}; 
   SUMA_GENERIC_PROG_OPTIONS_STRUCT *Opt=NULL;
   int kar;
   SUMA_Boolean brk;
   SUMA_Boolean LocalHead = NOPE;

   SUMA_ENTRY;
   
   Opt = SUMA_Alloc_Generic_Prog_Options_Struct();
   Opt->com = NULL;
   Opt->N_com = 0;
   Opt->b1 = 0;
   Opt->s = NULL;
   kar = 1;
   brk = NOPE;
	while (kar < argc) { /* loop accross command ine options */
		/*fprintf(stdout, "%s verbose: Parsing command line...\n", FuncName);*/
		if (ps) {
         if (strcmp(argv[kar], "-h") == 0 || strcmp(argv[kar], "-help") == 0) {
			    usage_DriveSuma(ps, strlen(argv[kar]) > 3 ? 2:1);
             exit (0);
		   }

		   SUMA_SKIP_COMMON_OPTIONS(brk, kar);
      }
      if (strcmp(argv[kar], "-echo_nel_stdout") == 0) {
         Opt->s = SUMA_copy_string("stdout:");
         brk = YUP;
      }

      if (strcmp(argv[kar], "-echo_nel_stderr") == 0) {
         Opt->s = SUMA_copy_string("stderr:");
         brk = YUP;
      }
      if (strcmp(argv[kar], "-echo_nel") == 0) {
         if (kar+1 >= argc)
         {
            fprintf (SUMA_STDERR, "need a paramter after -echo_nel \n");
            exit (1);
         }
         ++kar;
         if (strcmp(argv[kar], "stdout")==0) {
            Opt->s = SUMA_copy_string("stdout:");
         } else if (strcmp(argv[kar], "stderr")==0) {
            Opt->s = SUMA_copy_string("stderr:");
         } else {
            Opt->s = SUMA_append_replace_string("file:",argv[kar],"",0);
         }         
         brk = YUP;
      }
      
      if (strcmp(argv[kar], "-help_nido") == 0) {
         char *s = SUMA_NIDO_Info();
         fprintf (SUMA_STDOUT,"%s\n", s); 
         SUMA_free(s); s = NULL;
         exit (0);
      }

      if (!brk && (strcmp(argv[kar], "-debug") == 0))
      {
         if (kar+1 >= argc)
         {
            fprintf (SUMA_STDERR, "need a number after -debug \n");
            exit (1);
         }
         
         Opt->debug = atoi(argv[++kar]);
         brk = YUP;
      }
      
      if (!brk && (strcmp(argv[kar], "-C_demo") == 0))
      {
         Opt->b1 = 1;
         brk = YUP;  
      }
      
      if (!brk && ( (strcmp(argv[kar], "-examples") == 0) ) ) {
         fprintf(SUMA_STDOUT,"#Example commands for running DriveSuma\n\n");
         fprintf(SUMA_STDOUT,"#show_surf action\n%s\n", uDS_show_surf);
         fprintf(SUMA_STDOUT,"#node_xyz action\n%s\n", uDS_node_xyz);
         fprintf(SUMA_STDOUT,"#viewer_cont action\n%s\n", uDS_viewer_cont);
         fprintf(SUMA_STDOUT,"#recorder_cont action\n%s\n", uDS_recorder_cont);
         fprintf(SUMA_STDOUT,"#surf_cont action\n%s\n", uDS_surf_cont);
         fprintf(SUMA_STDOUT,"#Adieu\n%s\n", uDS_kill_suma);
         exit(0);          
      }

      if (!brk && (strcmp(argv[kar], "-com") == 0))
      {
         if (kar+1 >= argc)
         {
            fprintf (SUMA_STDERR, "need a number after -debug \n");
            exit (1);
         }
         
         Opt->com = (char **)SUMA_realloc(Opt->com, 
                                 sizeof(char *)*(Opt->N_com+1));
         Opt->com[Opt->N_com] = NULL;
         ++kar;
         do { 
            Opt->com[Opt->N_com] = 
               SUMA_append_replace_string (Opt->com[Opt->N_com], 
                                           argv[kar], " ", 1);
            ++kar;
            brk = NOPE;
            if ( kar >= argc ) brk = YUP;
            else if (strcmp(argv[kar], "-com") == 0) {
               --kar; brk = YUP;
            }
         } while (!brk);
         ++Opt->N_com;
         brk = YUP;
      }
      
      
      if (!brk && (!ps || !ps->arg_checked[kar])) {
			SUMA_S_Errv("Option %s not valid, or requires preceding -com option\n"
                     "Try -help for usage\n", argv[kar]);
         suggest_best_prog_option(argv[0], argv[kar]);
			if (Opt) Opt = SUMA_Free_Generic_Prog_Options_Struct(Opt);
         SUMA_RETURN(NULL); 
		} else {	
			brk = NOPE;
			kar ++;
		}
   }
   
   SUMA_RETURN(Opt);
}

SUMA_Boolean SUMA_ParseKeyModifiers(char *keyopt, int *Key_mult, 
                                    float *Key_pause, int *Key_redis, 
                                    char **strgvalp)
{
   static char FuncName[]={"SUMA_ParseKeyModifiers"};
   char *cccp=NULL, *op=NULL;
   int Found, v;
   double dv;
   SUMA_Boolean LocalHead = NOPE;
   SUMA_ENTRY;
   
   *Key_mult = 1;
   *Key_pause = 0.0;
   *Key_redis = 0;
   if (!strgvalp || *strgvalp) {
      SUMA_S_Err("strgvalp is NULL or point to not NULL");
   }  
   if (!keyopt || strncmp(keyopt,"-key", 4)) {
      SUMA_S_Errv("NULL or bad keyopt %s", SUMA_CHECK_NULL_STR(keyopt));
      SUMA_RETURN(NOPE);
   }
   Found = 1; 
   SUMA_LHv("keyopt=%s\n", keyopt);
   cccp = keyopt;
   do {
      if ((cccp = strstr(cccp,":"))) {/* found mods */
         SUMA_LHv("Now at =%s\n", cccp);
         /* what is it? */
         ++cccp;
         switch (cccp[0]) {
            case 'r':
               SUMA_ADVANCE_PAST_INT(cccp, v, Found);
               if (!Found) {
                  fprintf (SUMA_STDERR, 
                           "Failed to parse number after :r in %s\n", 
                           keyopt);
                  SUMA_RETURN(NOPE);
               }
               *Key_mult = v;
               break;
            case 'p':
               *Key_pause = -1; Found = 1;
               SUMA_LH("Will pause for each rep\n");
               break;
            case 's':
               ++cccp;  /* touchy for floats*/
               SUMA_ADVANCE_PAST_NUM(cccp, dv, Found);
               if (!Found) {
                  fprintf (SUMA_STDERR, 
                           "Failed to parse number after :s in %s\n", 
                           keyopt);
                  SUMA_RETURN(NOPE);
               }
               *Key_pause = (float)dv;
               SUMA_LHv("Will pause for %f secs\n", *Key_pause);
               break;
            case 'd':
               *Key_redis = 1;
               SUMA_LH("Will redisplay for each rep\n");
               break;
            case 'v':
               op = cccp;
               SUMA_SKIP_TO_NEXT_CHAR(cccp, NULL, ':');
               SUMA_COPY_TO_STRING(op, cccp, (*strgvalp));
               break;
            default:
               SUMA_S_Errv("Failed to parse content of %s\n", keyopt);
               Found = 0;
               break;
         }
      }
   } while (cccp && cccp[0] && Found);

   SUMA_RETURN(YUP);   
}
/*
A function for parsing command command options.
Words recognized here are flagged with a null char at the beginning of the identified strings
*/
int SUMA_DriveSuma_ParseCommon(NI_group *ngr, int argtc, char ** argt)
{
   static char FuncName[]={"SUMA_DriveSuma_ParseCommon"};
   int kar, N, nv, nums;
   double dv3[3], tmpd, dv12[12];
   char *stmp=NULL;
   SUMA_PARSED_NAME *fn;
   SUMA_Boolean brk = NOPE;
   SUMA_Boolean LocalHead = NOPE;

   SUMA_ENTRY;
   
   /* parse 'em */
   kar = 1;
   brk = NOPE;
	if (LocalHead) {
      fprintf(SUMA_STDERR, 
               "%s verbose: Parsing command line...\n"
               "Have %d entries with argt[0]='%s'", 
               FuncName, argtc, argt[0]);
	}
   while (kar < argtc) { /* loop accross command ine options */
      SUMA_LHv("Now processing argt[%d]=%s\n", 
               kar, SUMA_CHECK_NULL_STR(argt[kar]));
      if (!argt[kar]) {
         SUMA_S_Errv("Null entry!: argt[%d]=%s\n", 
                     kar, SUMA_CHECK_NULL_STR(argt[kar]));
         SUMA_RETURN(NOPE);
      }
      
      if (!brk && (  (strcmp(argt[kar], "-label") == 0) || 
                     (strcmp(argt[kar], "-surf_label") == 0) || 
                     (strcmp(argt[kar], "-so_label") == 0)))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a label after -surf_label \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         if (!NI_get_attribute(ngr, "SO_label")) 
            NI_set_attribute(ngr, "SO_label", argt[++kar]);
         else if (strcmp(NI_get_attribute(ngr, "SO_label"), argt[++kar])) { 
            SUMA_S_Err("Two options setting different  surface labels"); 
            SUMA_RETURN(0); 
         }
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && (  (strcmp(argt[kar], "-setSUMAenv") == 0) ))
      {
         int ienv = 0, closed = 0;
         char attr[32]={""}, *aval=NULL;
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, 
"need a string with 'NAME = VALUE' after -setSUMAenv (obey quotes and spaces) %d %d\n", kar, argtc);
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ienv = -1;
         do {
            ++ienv;
            sprintf(attr,"ENV.%d", ienv);
         } while (NI_get_attribute(ngr,attr));
         /* Now search for a quote before the name */
         ++kar;
         if (argt[kar][0] != '\'' && argt[kar][0] != '\"') {
            SUMA_S_Errv("You must enclose env expression with ' or \" quotes\n"
                        "Have open %s\n", argt[kar]);
            SUMA_RETURN(0);
         } 
         
         aval = SUMA_copy_quoted(argt[kar],NULL,'\0','\0', 1, 0, &closed);
         
         if (!aval) {
            SUMA_S_Err("Failed to get env value");
            SUMA_RETURN(0);
         }
         SUMA_LHv("Adding >>%s<< %d \n", aval, closed); 
         if (!closed) {
            SUMA_S_Errv("You must enclose env expression with ' or \" quotes\n"
                        "Have unterminated %s\n", aval);
            SUMA_RETURN(0);
         } 
         NI_set_attribute(ngr, attr, aval);
         SUMA_free(aval); aval=NULL;
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-switch_surf") == 0) ))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a surf label after -switch_surf \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         if (!NI_get_attribute(ngr, "SO_label")) 
            NI_set_attribute(ngr, "SO_label", argt[++kar]);
         else if (strcmp(NI_get_attribute(ngr, "SO_label"), argt[++kar])) { 
            SUMA_S_Err("Two options setting different  surface labels"); 
            SUMA_RETURN(0); 
         }
         NI_set_attribute(ngr, "switch_surf", argt[kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-switch_cmap") == 0) ))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a cmap name after -switch_cmap \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "switch_cmap", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-switch_cmode") == 0) ))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, 
                     "need a color mapping mode after -switch_cmode \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ++kar;
         if (strcasecmp(argt[kar],"nn") &&
             strcasecmp(argt[kar],"dir") &&
             strcasecmp(argt[kar],"int")) {
            fprintf(SUMA_STDERR,
                  "CMODE %s not allowed. Choose from 'NN', 'Dir', or 'Int'\n", 
                  argt[kar]);   
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "switch_cmode", argt[kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-load_cmap") == 0) ))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a cmap name after -load_cmap \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "load_cmap", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-dset_label") == 0) ))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a label after -dset_label \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "dset_label", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-switch_dset") == 0) ))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a dset label after -switch_dset \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "dset_label", argt[++kar]);
         NI_set_attribute(ngr, "switch_dset", argt[kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-load_dset") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a dset file after -load_dset \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         fn = SUMA_ParseFname(argt[++kar], SUMAg_CF->cwd);
         /* SUMA_ShowParsedFname(fn, NULL); */
         NI_set_attribute(ngr, "Dset_FileName", fn->FullName);
         fn = SUMA_Free_Parsed_Name(fn);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-load_col") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a color file after -load_col \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         fn = SUMA_ParseFname(argt[++kar], SUMAg_CF->cwd);
         /* SUMA_ShowParsedFname(fn, NULL); */
         NI_set_attribute(ngr, "Col_FileName", fn->FullName);
         fn = SUMA_Free_Parsed_Name(fn);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-I_sb") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need an index after -I_sb \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "I_sb", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-I_range") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need at least one value after -I_range \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         ++kar; N = 1; stmp = NULL; nums = 0;
         while (  kar < argtc && 
                  argt[kar] && 
                  SUMA_isNumString(argt[kar],(void *)((long int)N))) {
            stmp = SUMA_append_replace_string(stmp, argt[kar], " ", 1); ++nums;
            argt[kar][0] = '\0'; ++kar;
         } --kar;
         if (!stmp || nums < 1 || nums > 2) {
            SUMA_S_Err( "Bad format for -I_range option values;\n"
                        " 1 or 2 values allowed.");
            SUMA_RETURN(0);
         }
         nv = SUMA_StringToNum(stmp, (void *)dv3, 3,2);
         if (nv < 1 || nv > 2) {
            SUMA_S_Err("Bad range string.");
            SUMA_RETURN(0);
         }else {
            if (nv == 1) { dv3[0] = -SUMA_ABS(dv3[0]); dv3[1] = -dv3[0]; }
            else if (dv3[0] > dv3[1]) { 
               tmpd = dv3[0]; dv3[0] = dv3[1]; dv3[1] = tmpd; 
            }
            /* have range, set it please */
            SUMA_free(stmp); stmp = NULL; 
            stmp = (char *)SUMA_malloc(sizeof(char)*nv*50);
            sprintf(stmp,"%f , %f", dv3[0], dv3[1]);
            NI_set_attribute(ngr, "I_range", stmp);
            SUMA_LHv("Range of %s\n", stmp);
            SUMA_free(stmp); stmp = NULL;
         }
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-bkg_col") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need at least 3 values after -bkg_col \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         ++kar; N = 1; stmp = NULL; nums = 0;
         while (  kar < argtc && 
                  argt[kar] && 
                  SUMA_isNumString(argt[kar],(void *)((long int)N))) {
            stmp = SUMA_append_replace_string(stmp, argt[kar], " ", 1); ++nums;
            argt[kar][0] = '\0'; ++kar;
         } --kar;
         if (!stmp || nums < 3 || nums > 4) {
            SUMA_S_Err( "Bad format for -bkg_col option values;\n"
                        " 3 or 4 values allowed.");
            SUMA_RETURN(0);
         }
         if (nums == 3) {
            stmp = SUMA_append_replace_string(stmp, "1.0", " ", 1); ++nums;
         }
         nv = SUMA_StringToNum(stmp, (void *)dv12, 12,nums);
         if (nv < 3 || nv > 4) {
            SUMA_S_Err("Bad range string.");
            SUMA_RETURN(0);
         }else {
            /* have range, set it please */
            SUMA_free(stmp); stmp = NULL; 
            stmp = (char *)SUMA_malloc(sizeof(char)*nv*50);
            sprintf(stmp,"%f , %f, %f, %f", dv12[0], dv12[1], dv12[2], dv12[3]);
            NI_set_attribute(ngr, "bkg_col", stmp);
            SUMA_LHv("bkg_col of %s\n", stmp);
            SUMA_free(stmp); stmp = NULL;
         }
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-autorecord") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a prefix after -autorecord\n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "autorecord", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }

      if (!brk && ( (strcmp(argt[kar], "-Dsp") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need XXX, Col, Con, or C&C after -Dsp \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "Dsp", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }

      if (!brk && ( (strcmp(argt[kar], "-B_sb") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need an index after -B_sb \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "B_sb", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-B_range") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need at least one value after -B_range \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         ++kar; N = 1; stmp = NULL; nums = 0;
         while (  kar < argtc && 
                  argt[kar] && 
                  SUMA_isNumString(argt[kar],(void *)((long int)N))) {
            stmp = SUMA_append_replace_string(stmp, argt[kar], " ", 1); ++nums;
            argt[kar][0] = '\0'; ++kar;
         } --kar;
         if (!stmp || nums < 1 || nums > 2) {
            SUMA_S_Err( "Bad format for -B_range option values;\n"
                        " 1 or 2 values allowed.");
            SUMA_RETURN(0);
         }
         nv = SUMA_StringToNum(stmp, (void *)dv3, 3,2);
         if (nv < 1 || nv > 2) {
            SUMA_S_Err("Bad range string.");
            SUMA_RETURN(0);
         }else {
            if (nv == 1) { dv3[0] = -SUMA_ABS(dv3[0]); dv3[1] = -dv3[0]; }
            else if (dv3[0] > dv3[1]) { 
               tmpd = dv3[0]; dv3[0] = dv3[1]; dv3[1] = tmpd; 
            }
            /* have range, set it please */
            SUMA_free(stmp); stmp = NULL; 
            stmp = (char *)SUMA_malloc(sizeof(char)*nv*50);
            sprintf(stmp,"%f , %f", dv3[0], dv3[1]);
            NI_set_attribute(ngr, "B_range", stmp);
            SUMA_LHv("Range of %s\n", stmp);
            SUMA_free(stmp); stmp = NULL;
         }
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-B_scale") == 0) ) )
      {
         if (kar+2 >= argtc)
         {
            fprintf (SUMA_STDERR, "need two values after -B_scale \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         ++kar; N = 1; stmp = NULL; nums = 0;
         while (  kar < argtc && 
                  argt[kar] && 
                  SUMA_isNumString(argt[kar],(void *)((long int)N))) {
            stmp = SUMA_append_replace_string(stmp, argt[kar], " ", 1); ++nums;
            argt[kar][0] = '\0'; ++kar;
         } --kar;
         if (!stmp || nums != 2) {
            SUMA_S_Err( "Bad format for -B_scale option values;\n"
                        " 2 values needed.");
            SUMA_RETURN(0);
         }
         nv = SUMA_StringToNum(stmp, (void *)dv3, 3,2);
         if ( nv != 2) {
            SUMA_S_Err("Bad scale string.");
            SUMA_RETURN(0);
         }else {
            if (dv3[0] > dv3[1]) { 
               tmpd = dv3[0]; dv3[0] = dv3[1]; dv3[1] = tmpd; 
            }
            /* have scale, set it please */
            SUMA_free(stmp); stmp = NULL; 
            stmp = (char *)SUMA_malloc(sizeof(char)*nv*50);
            sprintf(stmp,"%f , %f", dv3[0], dv3[1]);
            NI_set_attribute(ngr, "B_scale", stmp);
            SUMA_LHv("Scale of %s\n", stmp);
            SUMA_free(stmp); stmp = NULL;
         }
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-T_sb") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need an index after -T_sb \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "T_sb", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-T_val") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a value after -T_val \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "T_val", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-Dim") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a value after -Dim \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "Dim", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-Opa") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a value after -Opa \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "Opa", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-Clst") == 0) ||
                    (strcmp(argt[kar], "-Clust") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need two values after -Clust \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         ++kar; N = 1; stmp = NULL; nums = 0;
         while (  kar < argtc && 
                  argt[kar] && 
                  SUMA_isNumString(argt[kar],(void *)((long int)N))) {
            stmp = SUMA_append_replace_string(stmp, argt[kar], " ", 1); ++nums;
            argt[kar][0] = '\0'; ++kar;
         } --kar;
         if (!stmp || nums != 2) {
            SUMA_S_Err( "Bad format for -Clst option values;\n"
                        " 2 and only 2 values allowed.");
            SUMA_RETURN(0);
         }
         nv = SUMA_StringToNum(stmp, (void *)dv3, 3,2);
         if (nv < 1 || nv > 2) {
            SUMA_S_Err("Bad Clst string.");
            SUMA_RETURN(0);
         }else {
            /* have range, set it please */
            SUMA_free(stmp); stmp = NULL; 
            stmp = (char *)SUMA_malloc(sizeof(char)*nv*50);
            sprintf(stmp,"%f , %f", dv3[0], dv3[1]);
            NI_set_attribute(ngr, "Clst", stmp);
            SUMA_LHv("Clst of %s\n", stmp);
            SUMA_free(stmp); stmp = NULL;
         }
         brk = YUP;
      }
      
      if (!brk && (  (strcmp(argt[kar], "-UseClst") == 0) ||
                     (strcmp(argt[kar], "-UseClust") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a 'y/n' after -UseClust \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ++kar;
         if (argt[kar][0] == 'y' || argt[kar][0] == 'Y')  
            NI_set_attribute(ngr, "UseClst", "y");
         else if (argt[kar][0] == 'n' || argt[kar][0] == 'N')  
            NI_set_attribute(ngr, "UseClst", "n");
         else {
            fprintf (SUMA_STDERR, "need a 'y/n' after -UseClust \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         brk = YUP;
      }
   
      
      if (!brk && (strcmp(argt[kar], "-viewer") == 0))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, 
                     "need a viewer (A-F) or (0-5) after -viewer \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "SV_id", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && (strcmp(argt[kar], "-1_only") == 0))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a 'y/n' after -1_only \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ++kar;
         if (argt[kar][0] == 'y' || argt[kar][0] == 'Y')  
            NI_set_attribute(ngr, "1_only", "y");
         else if (argt[kar][0] == 'n' || argt[kar][0] == 'N')  
            NI_set_attribute(ngr, "1_only", "n");
         else {
            fprintf (SUMA_STDERR, "need a 'y/n' after -1_only \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         brk = YUP;
      }

      if (!brk && (  (strcmp(argt[kar], "-shw_0") == 0) ||
                     (strcmp(argt[kar], "-show_0") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a 'y/n' after -show_0 \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ++kar;
         if (argt[kar][0] == 'y' || argt[kar][0] == 'Y')  
            NI_set_attribute(ngr, "shw_0", "y");
         else if (argt[kar][0] == 'n' || argt[kar][0] == 'N')  
            NI_set_attribute(ngr, "shw_0", "n");
         else {
            fprintf (SUMA_STDERR, "need a 'y/n' after -show_0 \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      
      if (!brk && (strcmp(argt[kar], "-view_dset") == 0))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a 'y/n' after -view_dset \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ++kar;
         if (argt[kar][0] == 'y' || argt[kar][0] == 'Y')  
            NI_set_attribute(ngr, "view_dset", "y");
         else if (argt[kar][0] == 'n' || argt[kar][0] == 'N')  
            NI_set_attribute(ngr, "view_dset", "n");
         else {
            fprintf (SUMA_STDERR, "need a 'y/n' after -view_dset \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && (strcmp(argt[kar], "-view_surf") == 0))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a 'y/n' after -view_surf \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ++kar;
         if (argt[kar][0] == 'y' || argt[kar][0] == 'Y')  
            NI_set_attribute(ngr, "view_surf", "y");
         else if (argt[kar][0] == 'n' || argt[kar][0] == 'N')  
            NI_set_attribute(ngr, "view_surf", "n");
         else {
            fprintf (SUMA_STDERR, "need a 'y/n' after -view_surf \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && (strcmp(argt[kar], "-RenderMode") == 0))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a valid string after -RenderMode \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ++kar;
         if (argt[kar][0] == 'V' || argt[kar][0] == 'v')  
            NI_set_attribute(ngr, "view_surf", "Viewer");
         else if (argt[kar][0] == 'F' || argt[kar][0] == 'f')  
            NI_set_attribute(ngr, "view_surf", "Fill");
         else if (argt[kar][0] == 'L' || argt[kar][0] == 'l')  
            NI_set_attribute(ngr, "view_surf", "Line");
         else if (argt[kar][0] == 'P' || argt[kar][0] == 'p')  
            NI_set_attribute(ngr, "view_surf", "Points");
         else if (argt[kar][0] == 'H' || argt[kar][0] == 'h')  
            NI_set_attribute(ngr, "view_surf", "Hide");
         else {
            fprintf (SUMA_STDERR, "need a valid string after -view_surf \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && (strcmp(argt[kar], "-TransMode") == 0))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, 
                     "need a valid string/value after -TransMode \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ++kar;
         if (argt[kar][0] == 'V' || argt[kar][0] == 'v')  
            NI_set_attribute(ngr, "trans_surf", "Viewer");
         else if (strstr(argt[kar],"%")) {
            char stmp[32]={""};
            for (N=0; (N<strlen(argt[kar]) && argt[kar][N]!='%' && N<16); ++N) {
               stmp[N] = argt[kar][N];
            }
            stmp[N]='\0';
            N = (int)strtol(stmp, NULL,10);
            if (N < 0 || N > 100) {
               fprintf (SUMA_STDERR, 
                        "Tansparency percentage should be between 0 and 100\n"
                        "have %d from %s\n", N, argt[kar]);
               SUMA_RETURN(0);
            }
            N = (int)(N*16.0/100);
            NI_SET_INT(ngr, "trans_surf", N);
         } else { /* read an int, should be between 0 and 16 */
            N = (int)strtol(argt[kar], NULL,10);
            if (N < 0 || N > 100) {
               fprintf (SUMA_STDERR, 
                        "Tansparency index should be between 0 and 16\n"
                        "have %d from %s\n", N, argt[kar]);
               SUMA_RETURN(0);
            }
            NI_SET_INT(ngr, "trans_surf", N);
         } 
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && (strcmp(argt[kar], "-view_surf_cont") == 0))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a 'y/n' after -view_surf_cont \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         ++kar;
         if (argt[kar][0] == 'y' || argt[kar][0] == 'Y')  
            NI_set_attribute(ngr, "View_Surf_Cont", "y");
         else if (argt[kar][0] == 'n' || argt[kar][0] == 'N')  
            NI_set_attribute(ngr, "View_Surf_Cont", "n");
         else {
            fprintf (SUMA_STDERR, "need a 'y/n' after -view_surf_cont \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && (strncmp(argt[kar], "-key", 4) == 0))
      {
         int N_Key = 0, Key_mult = 1, Key_redis= 0;
         char *Key_strval=NULL;
         char stmp[100];
         float Key_pause = 0;
         
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a key after -key \n");
            SUMA_RETURN(0);
         }
         
         if (!SUMA_ParseKeyModifiers(argt[kar], 
                                    &Key_mult, 
                                    &Key_pause, 
                                    &Key_redis, 
                                    &Key_strval)) {
            SUMA_S_Errv("Failed in parsing %s\n", argt[kar]);
            SUMA_RETURN(0);
         } 

         
         argt[kar][0] = '\0';
         ++kar;
         if (!NI_get_attribute(ngr,"N_Key")) NI_SET_INT(ngr,"N_Key", 0);
         NI_GET_INT(ngr, "N_Key", N_Key); 
         sprintf(stmp, "Key_%d", N_Key);
         NI_SET_STR(ngr, stmp, argt[kar]);
         sprintf(stmp, "Key_rep_%d", N_Key);
         NI_SET_INT(ngr, stmp, Key_mult);
         sprintf(stmp, "Key_pause_%d", N_Key);
         NI_SET_FLOAT(ngr, stmp, Key_pause);
         sprintf(stmp, "Key_redis_%d", N_Key);
         NI_SET_INT(ngr, stmp, Key_redis);
         sprintf(stmp, "Key_strval_%d", N_Key);
         if (Key_strval) {
            NI_set_attribute(ngr, stmp, Key_strval);
            SUMA_free(Key_strval);
         }
         argt[kar][0] = '\0';
         ++N_Key;
         NI_SET_INT(ngr,"N_Key", N_Key);
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-load_view") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a .vvs file after -load_view \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "VVS_FileName", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-N_foreg_smooth") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need an integer after -N_foreg_smooth \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         ++kar; nums = (int)strtol(argt[kar], NULL,10);
         if (nums < 0 || nums > 500) {
            SUMA_S_Errv("Bad integer for option -N_foreg_smooth %s\n",
                     argt[kar]);
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "N_foreg_smooth", argt[kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-N_final_smooth") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need an integer after -N_final_smooth \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         ++kar; nums = (int)strtol(argt[kar], NULL,10);
         if (nums < 0 || nums > 500) {
            SUMA_S_Errv("Bad integer for option -N_final_smooth %s\n",
                     argt[kar]);
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "N_final_smooth", argt[kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-inout_notify") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a value after -inout_notify\n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         ++kar;
         if (argt[kar][0] == 'y' || argt[kar][0] == 'Y')  
            NI_set_attribute(ngr, "inout_notify", "y");
         else if (argt[kar][0] == 'n' || argt[kar][0] == 'N')  
            NI_set_attribute(ngr, "inout_notify", "n");
         else {
            fprintf (SUMA_STDERR, "need a 'y/n' after -view_surf \n");
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';
         brk = YUP;
         
      }
      
      if (!brk && ( (strcmp(argt[kar], "-load_do") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a .do file after -load_do \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';
         NI_set_attribute(ngr, "DO_FileName", argt[++kar]);
         argt[kar][0] = '\0';
         brk = YUP;
      }


      if (!brk && ( (strncmp(argt[kar], "-fixed_do",9) == 0) ||
                    (strncmp(argt[kar], "-Fixed_do",9) == 0) ||
                    (strncmp(argt[kar], "-mobile_do",10) == 0) ||
                    (strncmp(argt[kar], "-Mobile_do",10) == 0) ) )
      {
         char *sbuf=NULL, *qar=NULL;
         NI_element *nel=NULL;
         int showit=0;
         if (argt[kar][1] == 'F' || argt[kar][1] == 'M') showit=1;
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, 
                     "need a string after -fixed_do (or -mobile_do)\n");
            SUMA_RETURN(0);
         }
         qar = UNIQ_hashcode(argt[kar]);
         if (strstr(argt[kar],"ixed_do")) {
            sbuf = SUMA_copy_string("<nido_head coord_type = 'fixed'\n"
                                 "default_color = '1.0 1.0 1.0'\n"
                                 "default_font = 'he18'\n"
                                 "idcode_str = ");
         } else {
            sbuf = SUMA_copy_string("<nido_head coord_type = 'mobile'\n"
                                 "default_SO_label = 'CURRENT'\n"
                                 "bond = 'surface'\n"
                                 "idcode_str = ");
         }
         sbuf = SUMA_append_replace_string(sbuf,qar,"",1);
         argt[kar][0] = '\0';
         free(qar); qar=NULL;
         sbuf = SUMA_append_replace_string(sbuf,"/>\n","\n",1);
         ++kar;
         if (!(qar = args_in_niml_quotes(argt, &kar, argtc, 1))) {
            SUMA_S_Errv("Could not find niml element starting at %s\n",
                        argt[kar]);
         } else {
            /* check that the new element is OK, that function reads 
               just one element*/
            if (!(nel=NI_read_element_fromstring(qar))) {
               SUMA_S_Errv("Could not parse -fixed_do %s\n"
                  "Try experimenting with niccc -s to get the syntax right.\n",
                        argt[kar]);
               exit(1);
            }
            if (showit) SUMA_ShowNel(nel);
            if (nel) NI_free_element(nel); nel=NULL;   
            sbuf = SUMA_append_replace_string(sbuf, qar,"",1);
            SUMA_free(qar); qar=NULL;
         }
         
         NI_set_attribute(ngr, "DO_FileName", sbuf);
         SUMA_free(sbuf); sbuf=NULL;
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-anim_dup") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a positive integer after -anim_dup \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';++kar;
         
         if (atoi(argt[kar]) < 0) {
            fprintf (SUMA_STDERR, "need a positive integer after -anim_dup \n");
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "Anim_Dup", argt[kar]);
         
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-save_as") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a PREFIX.EXT  after -save_as \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';++kar;
         
         NI_set_attribute(ngr, "Save_As", argt[kar]);
         
         argt[kar][0] = '\0';
         brk = YUP;
      }
      if (!brk && ( (strcmp(argt[kar], "-save_range") == 0) ) )
      {
         if (kar+2 >= argtc)
         {
            fprintf (SUMA_STDERR, "need 2 numbers after -save_from \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';++kar;
         NI_SET_INT(ngr, "Save_From", atoi(argt[kar]));
         argt[kar][0] = '\0';++kar;
         NI_SET_INT(ngr, "Save_To", atoi(argt[kar]));
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-save_last") == 0) ) )
      {
         
         NI_SET_INT(ngr, "Save_From", -1);
         NI_SET_INT(ngr, "Save_To", 0);
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (!brk && ( (strcmp(argt[kar], "-save_index") == 0) ) )
      {
         
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a number after -save_index \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';++kar;
         NI_SET_INT(ngr, "Save_From", atoi(argt[kar]));
         NI_SET_INT(ngr, "Save_To", atoi(argt[kar]));
         
         argt[kar][0] = '\0';
         brk = YUP;
      }
      if (!brk && ( (strcmp(argt[kar], "-save_last_n") == 0) ) )
      {
         
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a number after -save_last_n \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';++kar;
         if (atoi(argt[kar]) <= 0) {
            fprintf (SUMA_STDERR, "need a number > 0 after -save_last_n\n");
            SUMA_RETURN(0);
         }
         NI_SET_INT(ngr, "Save_From", -atoi(argt[kar]));
         NI_SET_INT(ngr, "Save_To", 0);
         
         argt[kar][0] = '\0';
         brk = YUP;
      }
      if (!brk && ( (strcmp(argt[kar], "-save_all") == 0) ) )
      {
         
         NI_SET_INT(ngr, "Save_From", 0);
         NI_SET_INT(ngr, "Save_To", 0);
         
         argt[kar][0] = '\0';
         brk = YUP;
      }
      if (  !brk && 
            (  (strcmp(argt[kar], "-caller_working_dir") == 0) || 
               (strcmp(argt[kar], "-cwd") == 0)) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a path after -caller_working_dir \n");
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';++kar;
         
         NI_set_attribute(ngr, "Caller_Working_Dir", argt[kar]);
         
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (  !brk && 
            (  (strcmp(argt[kar], "-viewer_width") == 0) ||
               (strcmp(argt[kar], "-width") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need 1 number after %s \n", argt[kar]);
            SUMA_RETURN(0);
         }
         
         argt[kar][0] = '\0';++kar;
         if (atoi(argt[kar]) < 10 || atoi(argt[kar]) > 2000) {
            fprintf (SUMA_STDERR, 
               "Have %d for width in pixels! \n", atoi(argt[kar]));
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "WindWidth", argt[kar]);
         NI_set_attribute(ngr, "DoViewerSetup","y"); /* flag indicating 
                                                      need to setup viewer, 
                                                      a la vvs */
        
         argt[kar][0] = '\0';
         brk = YUP;
      }
      
      if (  !brk && 
            (  (strcmp(argt[kar], "-viewer_height") == 0) ||
               (strcmp(argt[kar], "-height") == 0) ) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need 1 number after %s \n", argt[kar]);
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';++kar;
         if (atoi(argt[kar]) < 10 || atoi(argt[kar]) > 2000) {
            fprintf (SUMA_STDERR, 
               "Have %d for height in pixels! \n", atoi(argt[kar]));
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "WindHeight", argt[kar]);
         NI_set_attribute(ngr, "DoViewerSetup","y"); /* flag indicating 
                                                      need to setup viewer, 
                                                      a la vvs */
         argt[kar][0] = '\0';
         brk = YUP;
      }
      if (  !brk && 
            (  (strcmp(argt[kar], "-viewer_size") == 0)  ) )
      {
         if (kar+2 >= argtc)
         {
            fprintf (SUMA_STDERR, "need 2 numbers after %s \n", argt[kar]);
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';++kar;
         if (atoi(argt[kar]) < 10 || atoi(argt[kar]) > 2000) {
            fprintf (SUMA_STDERR, 
               "Have %d for width in pixels! \n", atoi(argt[kar]));
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "WindWidth", argt[kar]);
         argt[kar][0] = '\0';++kar;
         if (atoi(argt[kar]) < 10 || atoi(argt[kar]) > 2000) {
            fprintf (SUMA_STDERR, 
               "Have %d for height in pixels! \n", atoi(argt[kar]));
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "WindHeight", argt[kar]);
         NI_set_attribute(ngr, "DoViewerSetup","y"); /* flag indicating 
                                                      need to setup viewer, 
                                                      a la vvs */
         argt[kar][0] = '\0';
         brk = YUP;
      }
      if (  !brk && 
            (  (strcmp(argt[kar], "-viewer_position") == 0)  ) )
      {
         if (kar+2 >= argtc)
         {
            fprintf (SUMA_STDERR, "need 2 numbers after %s \n", argt[kar]);
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';++kar;
         if (atoi(argt[kar]) < 0 || atoi(argt[kar]) > 4000) {
            fprintf (SUMA_STDERR, 
               "Have %d for X in pixels. Range [0 4000].! \n", atoi(argt[kar]));
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "WindX", argt[kar]);
         argt[kar][0] = '\0';++kar;
         if (atoi(argt[kar]) < 0 || atoi(argt[kar]) > 4000) {
            fprintf (SUMA_STDERR, 
               "Have %d for Y in pixels!  Range [0 4000].\n", atoi(argt[kar]));
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "WindY", argt[kar]);
         NI_set_attribute(ngr, "DoViewerSetup","y"); /* flag indicating 
                                                      need to setup viewer, 
                                                      a la vvs */
         argt[kar][0] = '\0';
         brk = YUP;
      }
      if (  !brk && 
            (  (strcmp(argt[kar], "-controller_position") == 0)  ) )
      {
         if (kar+2 >= argtc)
         {
            fprintf (SUMA_STDERR, "need 2 numbers after %s \n", argt[kar]);
            SUMA_RETURN(0);
         }
         argt[kar][0] = '\0';++kar;
         if (atoi(argt[kar]) < 0 || atoi(argt[kar]) > 4000) {
            fprintf (SUMA_STDERR, 
               "Have %d for X in pixels. Range [0 4000].! \n", atoi(argt[kar]));
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "ContX", argt[kar]);
         argt[kar][0] = '\0';++kar;
         if (atoi(argt[kar]) < 0 || atoi(argt[kar]) > 4000) {
            fprintf (SUMA_STDERR, 
               "Have %d for Y in pixels!  Range [0 4000].\n", atoi(argt[kar]));
            SUMA_RETURN(0);
         }
         NI_set_attribute(ngr, "ContY", argt[kar]);
         NI_set_attribute(ngr, "DoViewerSetup","y"); /* flag indicating 
                                                      need to setup viewer, 
                                                      a la vvs */
         argt[kar][0] = '\0';
         brk = YUP;
      }
      if (0 && !brk) { /* do not enforce this here */
			fprintf (SUMA_STDERR,
                  "Error %s:\n"
                  "Option %s not understood. Try -help for usage\n",
               FuncName, argt[kar]);
         SUMA_RETURN(0);
		} else {	
			brk = NOPE;
			kar ++;
		}
   }

   if (!NI_get_attribute(ngr, "Caller_Working_Dir")) {
      NI_set_attribute(ngr, "Caller_Working_Dir", SUMAg_CF->cwd);
   }
   SUMA_RETURN(YUP);
}


char ** SUMA_free_com_argv(char **argt, int *argtc)
{
   static char FuncName[]={"SUMA_free_com_argv"};
   int i;
   
   SUMA_ENTRY;
   
   if (argt) {
      for (i=0; i<*argtc; ++i) if (argt[i]) SUMA_free(argt[i]); 
      SUMA_free(argt); argt = NULL;
   }
   
   *argtc = -1;
   SUMA_RETURN(NULL);
}

/*!
   \brief char ** SUMA_com2argv(char *com, int *argtcp)
   Turn a command into an argv, argc duo
   Free argv with SUMA_free_com_argv
*/
char ** SUMA_com2argv(char *com, int *argtcp) 
{
   static char FuncName[]={"SUMA_com2argv"};
   char **argt=NULL, *pos, *tp=NULL;
   int argtc = 0;
   SUMA_Boolean LocalHead = NOPE;
   
   SUMA_ENTRY;
   
   *argtcp = -1;
   
   /* change com to a bunch of arguments */
   /* get the type */
   SUMA_GET_BETWEEN_BLANKS(com, NULL, pos);
   tp = NULL; SUMA_COPY_TO_STRING(com, pos, tp); com = pos;
   if (!tp) { /* nothing to see here */
      *argtcp = 0;
      SUMA_RETURN(NULL);
   }
   SUMA_LHv("Adding >>>%s<<<\n", tp);
   argt = (char **)SUMA_realloc(argt, sizeof(char *)*(argtc+2)); {
      argt[argtc] = SUMA_copy_string("drivesumacom"); ++argtc; 
      argt[argtc] = tp; tp = NULL; ++argtc;
   }
   /* get whatever else follows */
   while (com[0]) {
      SUMA_GET_BETWEEN_BLANKS(com, NULL, pos);
      tp=NULL;SUMA_COPY_TO_STRING(com, pos, tp); com = pos;
      SUMA_LHv("Adding other >>>%s<<<\n", tp);
      argt = (char **)SUMA_realloc(argt, sizeof(char *)*(argtc+1)); 
      argt[argtc] = tp; tp = NULL; 
      ++argtc;
   }
   
   *argtcp = argtc;
   SUMA_RETURN(argt);
}

SUMA_SurfaceObject *SUMA_ShowSurfComToSO(char *com)
{
   static char FuncName[]={"SUMA_ShowSurfComToSO"};
   SUMA_SurfaceObject *SO = NULL;
   SUMA_GENERIC_ARGV_PARSE *pst=NULL;
   char **argt=NULL, *pos, *tp=NULL;
   int argtc = 0;
   SUMA_SurfSpecFile *Spec = NULL;
   int *isin=NULL;
   int  i = -1, ii, jj, kk, il, N_Spec=0, kar=0;
   SUMA_Boolean brk = NOPE;
   SUMA_Boolean LocalHead = NOPE;
   
   SUMA_ENTRY;
   
   /* change com to a bunch of arguments */
   argt = SUMA_com2argv(com, &argtc); 

   /* now parse these fake options */
   pst = SUMA_Parse_IO_Args(argtc, argt, "-i;-t;-spec;-sv;");
   if (LocalHead) SUMA_Show_IO_args(pst);
   
   
   if (pst->s_N_surfnames + pst->i_N_surfnames + pst->t_N_surfnames != 1) {
      SUMA_S_Err("Multiple surface specifications used. Only one surface allowed.");
      exit(1);
   }

   Spec = SUMA_IO_args_2_spec(pst, &N_Spec);
   if (N_Spec == 0) {
      SUMA_S_Err("No surfaces found.");
      exit(1);
   }
   if (N_Spec != 1) {
      SUMA_S_Err("Multiple spec at input.");
      exit(1);
   }

   /* read in one surface for now */
   SO = SUMA_Load_Spec_Surf(Spec, 0, pst->sv[0], 0);
   if (!SO) {
         fprintf (SUMA_STDERR,"Error %s:\n"
                              "Failed to find surface\n"
                              "in spec file. \n",
                              FuncName );
         exit(1);
      
   }

   /* now search for some extra options */
   kar = 1;
   brk = NOPE;
	while (kar < argtc) { /* loop accross command ine options */
		/*fprintf(stdout, "%s verbose: Parsing command line...\n", FuncName);*/
      if (!brk && ( (strcmp(argt[kar], "-label") == 0) || (strcmp(argt[kar], "-surf_label") == 0) || (strcmp(argt[kar], "-so_label") == 0)))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a label after -surf_label \n");
            exit (1);
         }
         
         if (SO->Label) SUMA_free(SO->Label);
         SO->Label = SUMA_copy_string(argt[++kar]);
         brk = YUP;
      }
      
      if (!brk && (  (strcmp(argt[kar], "-group") == 0) || 
                     (strcmp(argt[kar], "-surf_group") == 0) || 
                     (strcmp(argt[kar], "-so_group") == 0)))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a label after -surf_group \n");
            exit (1);
         }
         
         if (SO->Group) SUMA_free(SO->Group);
         SO->Group = SUMA_copy_string(argt[++kar]);
         brk = YUP;
      }
      
      if (!brk && (  (strcmp(argt[kar], "-state") == 0) || 
                     (strcmp(argt[kar], "-surf_state") == 0) || 
                     (strcmp(argt[kar], "-so_state") == 0)))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a label after -surf_state \n");
            exit (1);
         }
         
         if (SO->State) SUMA_free(SO->State);
         SO->State = SUMA_copy_string(argt[++kar]);
         brk = YUP;
      }
      
      if (!brk && (  (strcmp(argt[kar], "-norm_dir") == 0) || 
                     (strcmp(argt[kar], "-surf_winding") == 0) )) 
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, 
                     "need a direction (cw or ccw) after -surf_winding \n");
            exit (1);
         }
         ++kar;
         if (  SUMA_iswordsame_ci("cw", argt[kar]) == 1 ||
               SUMA_iswordsame_ci("in", argt[kar]) == 1 || 
               SUMA_iswordsame_ci("-1", argt[kar]) == 1 ) {
            SO->normdir = -1;
         } else if ( SUMA_iswordsame_ci("ccw", argt[kar]) == 1 || 
                     SUMA_iswordsame_ci("out", argt[kar]) == 1 || 
                     SUMA_iswordsame_ci("1", argt[kar]) == 1) {
            SO->normdir = 1;
         } else {
            fprintf (SUMA_STDERR,
                     "Error %s:\n"
                     "value %s not valid with -surf_winding "
                     "(cw or ccw only acceptable)\n", 
                                    FuncName, argt[kar]);
            exit(1);
         }
         brk = YUP;
      }
      
      if (!brk && !pst->arg_checked[kar]) {
			fprintf (SUMA_STDERR,
                  "Error %s:\n"
                  "Option %s not understood. Try -help for usage\n",
               FuncName, argt[kar]);
			exit (1);
		} else {	
			brk = NOPE;
			kar ++;
		}
   }

   /* fix the trimmings */
   if (!SO->State) {SO->State = SUMA_copy_string("DC"); }
   if (!SO->Group) {SO->Group = SUMA_copy_string("DS"); }
   if (!SO->Label) {SO->Label = SUMA_copy_string("Benedictus"); }
   if (SO->Label) { 
      if (SO->idcode_str) SUMA_free(SO->idcode_str); 
      SO->idcode_str = NULL; SUMA_NEW_ID(SO->idcode_str, SO->Label); }

   if (LocalHead) {
      SUMA_Print_Surface_Object(SO, NULL);
   }
   /* clean up */
   argt = SUMA_free_com_argv(argt, &argtc);
   
   if (pst) SUMA_FreeGenericArgParse(pst); pst = NULL;
   if (N_Spec) {
      int k=0; 
      for (k=0; k<N_Spec; ++k) {
         if (!SUMA_FreeSpecFields(&(Spec[k]))) { SUMA_S_Err("Failed to free spec fields"); } 
      }
      SUMA_free(Spec); Spec = NULL; N_Spec = 0;
   }
   
   SUMA_RETURN(SO);
}


SUMA_SurfaceObject *SUMA_NodeXYZComToSO(char *com)
{
   static char FuncName[]={"SUMA_NodeXYZComToSO"};
   SUMA_SurfaceObject *SO = NULL;
   SUMA_GENERIC_ARGV_PARSE *pst=NULL;
   char **argt=NULL, *pos, *tp=NULL;
   int argtc = 0;
   SUMA_SurfSpecFile *Spec = NULL;
   int *isin=NULL;
   int  i = -1, ii, jj, kk, il, N_Spec=0, kar=0;
   SUMA_Boolean brk = NOPE;
   char *f1d = NULL;
   float *far = NULL;
   int ncol, nrow;
   SUMA_Boolean LocalHead = NOPE;
   
   SUMA_ENTRY;
   
   /* change com to a bunch of arguments */
   argt = SUMA_com2argv(com, &argtc); 
   
   /* now parse these fake options (have to do it, in case you need it later)*/
   pst = SUMA_Parse_IO_Args(argtc, argt, "-i;-t;-spec;-sv;");
   if (LocalHead) SUMA_Show_IO_args(pst);

   /* a necessary receptacle */
   SO = SUMA_Alloc_SurfObject_Struct(1);  
   
   /* parse 'em */
   kar = 1;
   brk = NOPE;
	while (kar < argtc) { /* loop accross command ine options */
		/*fprintf(stdout, "%s verbose: Parsing command line...\n", FuncName);*/
      if (!brk && ( (strcmp(argt[kar], "-label") == 0) || (strcmp(argt[kar], "-surf_label") == 0) || (strcmp(argt[kar], "-so_label") == 0)) )
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a label after -label \n");
            exit (1);
         }
         
         if (SO->Label) SUMA_free(SO->Label);
         SO->Label = SUMA_copy_string(argt[++kar]);
         brk = YUP;
      }
      
      if (!brk && (strcmp(argt[kar], "-xyz_1D") == 0))
      {
         if (kar+1 >= argtc)
         {
            fprintf (SUMA_STDERR, "need a 1D file after -xyz_1D \n");
            exit (1);
         }
         
         far=SUMA_Load1D_s(argt[++kar], &ncol, &nrow, 1, 0);
         SO->N_Node = nrow;
         SO->NodeDim = ncol;
         SO->NodeList = (float *)SUMA_calloc(nrow*ncol, sizeof(float));
         memcpy((void *)SO->NodeList, (void *)far, nrow*ncol * sizeof(float));
         free(far); far = NULL;
         brk = YUP;
      }
      
      if (!brk && !pst->arg_checked[kar]) {
			fprintf (SUMA_STDERR,"Error %s:\nOption %s not understood. Try -help for usage\n",
               FuncName, argt[kar]);
			exit (1);
		} else {	
			brk = NOPE;
			kar ++;
		}
   }

   /* fix the trimmings */
   if (!SO->State) {SO->State = SUMA_copy_string("DC"); }
   if (!SO->Group) {SO->Group = SUMA_copy_string("DS"); }
   if (!SO->Label) {SO->Label = SUMA_copy_string("Benedictus"); }
   if (SO->Label) { 
      if (SO->idcode_str) SUMA_free(SO->idcode_str); 
      SO->idcode_str = NULL; SUMA_NEW_ID(SO->idcode_str, SO->Label); 
   }

   if (LocalHead) {
      SUMA_Print_Surface_Object(SO, NULL);
   }
   /* clean up */
   argt = SUMA_free_com_argv(argt, &argtc);
   if (pst) SUMA_FreeGenericArgParse(pst); pst = NULL;
   if (N_Spec) {
      int k=0; 
      for (k=0; k<N_Spec; ++k) {
         if (!SUMA_FreeSpecFields(&(Spec[k]))) { SUMA_S_Err("Failed to free spec fields"); } 
      }
      SUMA_free(Spec); Spec = NULL; N_Spec = 0;
   }
   
   SUMA_RETURN(SO);
}


NI_group *SUMA_ComToNgr(char *com, char *command)
{
   static char FuncName[]={"SUMA_ComToNgr"};
   NI_group *ngr = NULL;   
   char **argt=NULL, *pos, *tp=NULL;
   int argtc = 0, kar = 0;
   SUMA_Boolean brk = NOPE;
   SUMA_Boolean LocalHead = NOPE;
   
   SUMA_ENTRY;
   
   if (!com || !command) {
      SUMA_S_Err("NULL input");
      SUMA_RETURN(NULL);
   }
   SUMA_LHv("Called with >%s<\n", com);
   /* change com to a bunch of arguments */
   argt = SUMA_com2argv(com, &argtc); 
   
   ngr = NI_new_group_element();
   NI_rename_group(ngr, "EngineCommand");
   NI_set_attribute(ngr, "Command", command);
   
   if (argtc > 0) {
      if (!SUMA_DriveSuma_ParseCommon(ngr, argtc, argt)) {
         SUMA_S_Err("Failed to parse common options.\n");
         NI_free_element(ngr); ngr = NULL;
         SUMA_RETURN(ngr);
      }
   }
   
   /* parse left overs */
   kar = 1;
   brk = NOPE;
	while (kar < argtc) { /* loop accross command ine options */
		/*fprintf(stdout, "%s verbose: Parsing command line...\n", FuncName);*/
      if (argt[kar][0] == '\0') { brk = YUP; } /* been take care of */
      
      if (!brk) {
			fprintf (SUMA_STDERR,
                  "Error %s:\n"
                  "Option %s not understood or not valid for command %s.\n"
                  " Try -help for usage\n",
               FuncName, argt[kar], NI_get_attribute(ngr, "Command"));
			NI_free_element(ngr); ngr = NULL;
         SUMA_RETURN(ngr);
		} else {	
			brk = NOPE;
			kar ++;
		}
   }

   if (LocalHead) {
      if (LocalHead) {
         int suc;
         SUMA_SL_Warn("writing NI group to DISK!");
         NEL_WRITE_TX(ngr, "stderr:", suc);
      }
   }
   
   /* clean up */
   argt = SUMA_free_com_argv(argt, &argtc);
   

   SUMA_RETURN(ngr);
}

