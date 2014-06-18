static char *afni_papers[] = {
   "\n" ,
   "            ****************************************************\n" ,
   "           ***** This is a list of papers about AFNI, SUMA, *****\n" ,
   "          ****** and various algorithms implemented therein ******\n" ,
   "----------------------------------------------------------------------------\n" ,
   "RW Cox.\n" ,
   "  AFNI: Software for analysis and visualization of functional\n" ,
   "  magnetic resonance neuroimages.  Computers and Biomedical Research,\n" ,
   "  29: 162-173, 1996.\n" ,
   "\n" ,
   "  * The very first AFNI paper, and the one I prefer you cite if you want\n" ,
   "    to refer to the AFNI package as a whole.\n" ,
   "  * http://afni.nimh.nih.gov/sscc/rwcox/papers/CBM_1996.pdf\n" ,
   "----------------------------------------------------------------------------\n" ,
   "RW Cox, A Jesmanowicz, and JS Hyde.\n" ,
   "  Real-time functional magnetic resonance imaging.\n" ,
   "  Magnetic Resonance in Medicine, 33: 230-236, 1995.\n" ,
   "\n" ,
   "  * The first paper on realtime FMRI; describes the algorithm used in\n" ,
   "    in the realtime plugin for time series regression analysis.\n" ,
   "  * http://afni.nimh.nih.gov/sscc/rwcox/papers/Realtime_FMRI.pdf\n" ,
   "----------------------------------------------------------------------------\n" ,
   "RW Cox and JS Hyde.\n" ,
   "  Software tools for analysis and visualization of FMRI Data.\n" ,
   "  NMR in Biomedicine, 10: 171-178, 1997.\n" ,
   "\n" ,
   "  * A second paper about AFNI and design issues for FMRI software tools.\n" ,
   "----------------------------------------------------------------------------\n" ,
   "RW Cox and A Jesmanowicz.\n" ,
   "  Real-time 3D image registration for functional MRI.\n" ,
   "  Magnetic Resonance in Medicine, 42: 1014-1018, 1999.\n" ,
   "\n" ,
   "  * Describes the algorithm used for image registration in 3dvolreg\n" ,
   "    and in the realtime plugin.\n" ,
   "  * The first paper to demonstrate realtime MRI volume image\n" ,
   "    registration running on a standard workstation (not a supercomputer).\n" ,
   "  * http://afni.nimh.nih.gov/sscc/rwcox/papers/RealtimeRegistration.pdf\n" ,
   "----------------------------------------------------------------------------\n" ,
   "ZS Saad, KM Ropella, RW Cox, and EA DeYoe.\n" ,
   "  Analysis and use of FMRI response delays.\n" ,
   "  Human Brain Mapping, 13: 74-93, 2001.\n" ,
   "\n" ,
   "  * Describes the algorithm used in 3ddelay (cf. '3ddelay -help').\n" ,
   "  * http://afni.nimh.nih.gov/sscc/rwcox/papers/Delays2001.pdf\n" ,
   "----------------------------------------------------------------------------\n" ,
   "ZS Saad, RC Reynolds, BD Argall, S Japee, RW Cox.\n" ,
   "  SUMA: An interface for surface-based intra- and inter-subject analysis\n" ,
   "  within AFNI.  2004 IEEE International Symposium on Biomedical Imaging:\n" ,
   "  from Nano to Macro.  IEEE, Arlington VA, pp. 1510-1513.\n" ,
   "\n" ,
   "  * A brief description of SUMA.\n" ,
   "  * http://dx.doi.org/10.1109/ISBI.2004.1398837\n" ,
   "  * http://afni.nimh.nih.gov/sscc/rwcox/papers/SUMA2004paper.pdf\n" ,
   "----------------------------------------------------------------------------\n" ,
   "ZS Saad, G Chen, RC Reynolds, PP Christidis, KR Hammett, PSF Bellgowan,\n" ,
   "  and RW Cox.  FIAC Analysis According to AFNI and SUMA.\n" ,
   "  Human Brain Mapping, 27: 417-424, 2006.\n" ,
   "\n" ,
   "  * Describes how we used AFNI to analyze the FIAC contest data.\n" ,
   "  * http://dx.doi.org/10.1002/hbm.20247\n" ,
   "  * http://afni.nimh.nih.gov/sscc/rwcox/papers/FIAC_AFNI_2006.pdf\n" ,
   "----------------------------------------------------------------------------\n" ,
   "BD Argall, ZS Saad, MS Beauchamp.\n" ,
   "  Simplified intersubject averaging on the cortical surface using SUMA.\n" ,
   "  Human Brain Mapping 27: 14-27, 2006.\n" ,
   "\n" ,
   "  * Describes the 'standard mesh' surface approach used in SUMA.\n" ,
   "  * http://dx.doi.org/10.1002/hbm.20158\n" ,
   "  * http://afni.nimh.nih.gov/sscc/rwcox/papers/SUMA2006paper.pdf\n" ,
   "----------------------------------------------------------------------------\n" ,
   "ZS Saad, DR Glen, G Chen, MS Beauchamp, R Desai, RW Cox.\n" ,
   "  A new method for improving functional-to-structural MRI alignment\n" ,
   "  using local Pearson correlation.  NeuroImage 44: 839-848, 2009.\n" ,
   "\n" ,
   "  * Describes the algorithm used in 3dAllineate (and thence in\n" ,
   "    align_epi_anat.py) for EPI-to-structural volume image registration.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2649831/\n" ,
   "  * http://dx.doi.org/10.1016/j.neuroimage.2008.09.037\n" ,
   "  * http://afni.nimh.nih.gov/sscc/rwcox/papers/LocalPearson2009.pdf\n" ,
   "----------------------------------------------------------------------------\n" ,
   "H Sarin, AS Kanevsky, SH Fung, JA Butman, RW Cox, D Glen, R Reynolds, and S Auh.\n" ,
   "  Metabolically stable bradykinin B2 receptor agonists enhance transvascular\n" ,
   "  drug delivery into malignant brain tumors by increasing drug half-life.\n" ,
   "  Journal of Translational Medicine, 7: #33, 2009.\n" ,
   "\n" ,
   "  * Describes the method used in AFNI for modeling dynamic contrast enhanced\n" ,
   "    (DCE) MRI for analysis of brain tumors.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2689161/\n" ,
   "  * http://dx.doi.org/10.1186/1479-5876-7-33\n" ,
   "----------------------------------------------------------------------------\n" ,
   "HJ Jo, ZS Saad, WK Simmons, LA Milbury, and RW Cox.\n" ,
   "  Mapping sources of correlation in resting state FMRI, with artifact detection\n" ,
   "  and removal.  NeuroImage, 52: 571-582, 2010.\n" ,
   "\n" ,
   "  * Describes the ANATICOR method for de-noising FMRI datasets.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2897154/\n" ,
   "  * http://dx.doi.org/10.1016/j.neuroimage.2010.04.246\n" ,
   "----------------------------------------------------------------------------\n" ,
   "A Vovk, RW Cox, J Stare, D Suput, and ZS Saad.\n" ,
   "  Segmentation Priors From Local Image Properties: Without Using Bias Field\n" ,
   "  Correction, Location-based Templates, or Registration.\n" ,
   "  Neuroimage, 55: 142-152, 2011.\n" ,
   "\n" ,
   "  * Describes the earliest basis for 3dSeg.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3031751/\n" ,
   "  * http://dx.doi.org/10.1016/j.neuroimage.2010.11.082\n" ,
   "----------------------------------------------------------------------------\n" ,
   "G Chen, ZS Saad, DR Glen, JP Hamilton, ME Thomason, IH Gotlib, and RW Cox.\n" ,
   "  Vector Autoregression, Structural Equation Modeling, and Their Synthesis in\n" ,
   "  Neuroimaging Data Analysis.\n" ,
   "  Computers in Biology and Medicine, 41: 1142-1155, 2011.\n" ,
   "\n" ,
   "  * Describes the method implemented in 1dSVAR (Structured Vector AutoRegression).\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3223325/\n" ,
   "  * http://dx.doi.org/10.1016/j.compbiomed.2011.09.004\n" ,
   "----------------------------------------------------------------------------\n" ,
   "RW Cox.\n" ,
   "  AFNI: what a long strange trip it's been.  NeuroImage, 62: 747-765, 2012.\n" ,
   "\n" ,
   "  * A Brief History of AFNI, from its inception to speculation about the future.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3246532/\n" ,
   "  * http://dx.doi.org/10.1016/j.neuroimage.2011.08.056\n" ,
   "----------------------------------------------------------------------------\n" ,
   "ZS Saad and RC Reynolds.\n" ,
   "  SUMA.  Neuroimage. 62: 768-773, 2012.\n" ,
   "\n" ,
   "  * The biography of SUMA.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3260385/\n" ,
   "  * http://dx.doi.org/10.1016/j.neuroimage.2011.09.016\n" ,
   "----------------------------------------------------------------------------\n" ,
   "G Chen, ZS Saad, AR Nath, MS Beauchamp, and RW Cox.\n" ,
   "  FMRI Group Analysis Combining Effect Estimates and Their Variances.\n" ,
   "  Neuroimage, 60: 747-765, 2012.\n" ,
   "\n" ,
   "  * The math behind 3dMEMA (Mixed Effects Meta-Analysis) -- AKA super-3dttest.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3404516/\n" ,
   "  * http://dx.doi.org/10.1016/j.neuroimage.2011.12.060\n" ,
   "----------------------------------------------------------------------------\n" ,
   "ZS Saad, SJ Gotts, K Murphy, G Chen, HJ Jo, A Martin, and RW Cox.\n" ,
   "  Trouble at Rest: How Correlation Patterns and Group Differences Become Distorted\n" ,
   "  After Global Signal Regression.\n" ,
   "  Brain Connectivity, 2: 25-32, 2012.\n" ,
   "\n" ,
   "  * Our first paper on why Global Signal Regression in resting state FMRI is\n" ,
   "    a bad idea when doing any form of group analysis.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3484684/\n" ,
   "  * http://dx.doi.org/10.1089/brain.2012.0080\n" ,
   "----------------------------------------------------------------------------\n" ,
   "SJ Gotts, WK Simmons, LA Milbury, GL Wallace, RW Cox, and A Martin.\n" ,
   "  Fractionation of Social Brain Circuits in Autism Spectrum Disorders.\n" ,
   "  Brain, 135: 2711-2725, 2012.\n" ,
   "\n" ,
   "  * In our humble opinion, this shows how to use resting state FMRI correctly when\n" ,
   "    making inter-group comparisons (hint: no global signal regresssion is used).\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3437021/\n" ,
   "  * http://dx.doi.org/10.1093/brain/aws160\n" ,
   "----------------------------------------------------------------------------\n" ,
   "HJ Jo, ZS Saad, SJ Gotts, A Martin, and RW Cox.\n" ,
   "  Quantifying Agreement between Anatomical and Functional Interhemispheric\n" ,
   "  Correspondences in the Resting Brain.\n" ,
   "  PLoS ONE, 7: art.no. e48847, 2012.\n" ,
   "\n" ,
   "  * A numerical method for measuring symmetry in brain functional imaging data.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3493608/\n" ,
   "  * http://dx.doi.org/10.1371/journal.pone.0048847\n" ,
   "----------------------------------------------------------------------------\n" ,
   "ZS Saad, SJ Gotts, K Murphy, G Chen, HJ Jo, A Martin, and RW Cox.\n" ,
   "  Trouble at Rest: How Correlation Patterns and Group Differences Become\n" ,
   "  Distorted After Global Signal Regression.  Brain Connectivity, 2012: 25-32.\n" ,
   "\n" ,
   "  * Another paper in the battle against Global Signal Regression.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3484684/\n" ,
   "  * http://dx.doi.org/10.1089/brain.2012.0080\n" ,
   "----------------------------------------------------------------------------\n" ,
   "G Chen, ZS Saad, JC Britton, DS Pine, and RW Cox\n" ,
   "  Linear mixed-effects modeling approach to FMRI group analysis.\n" ,
   "  NeuroImage, 73: 176-190, 2013.\n" ,
   "\n" ,
   "  * The math behind 3dLME.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3404516/\n" ,
   "  * http://dx.doi.org/10.1016/j.neuroimage.2011.12.060\n" ,
   "----------------------------------------------------------------------------\n" ,
   "SJ Gotts, ZS Saad, HJ Jo, GL Wallace, RW Cox, and A Martin.\n" ,
   "  The perils of global signal regression for group comparisons: A case study\n" ,
   "  of Autism Spectrum Disorders.\n" ,
   "  Frontiers in Human Neuroscience: art.no. 356, 2013.\n" ,
   "\n" ,
   "  * The long twilight struggle against Global Signal Regression continues.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3709423/\n" ,
   "  * http://dx.doi.org/10.3389/fnhum.2013.00356\n" ,
   "----------------------------------------------------------------------------\n" ,
   "HJ Jo, SJ Gotts, RC Reynolds, PA Bandettini, A Martin, RW Cox, and ZS Saad.\n" ,
   "  Effective preprocessing procedures virtually eliminate distance-dependent\n" ,
   "  motion artifacts in resting state FMRI.\n" ,
   "  Journal of Applied Mathematics:  art.no. 935154, 2013.\n" ,
   "\n" ,
   "  * A reply to the Power 2012 paper on pre-processing resting state FMRI data,\n" ,
   "    showing how they got it wrong.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3886863/\n" ,
   "  * http://dx.doi.org/10.1155/2013/935154\n" ,
   "----------------------------------------------------------------------------\n" ,
   "SJ Gotts, HJ Jo, GL Wallace, ZS Saad, RW Cox, and A Martin.\n" ,
   "  Two distinct forms of functional lateralization in the human brain.\n" ,
   "  PNAS, 110: E3435-E3444, 2013.\n" ,
   "\n" ,
   "  * More about methodology and results for symmetry in brain function.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3767540/\n" ,
   "  * http://dx.doi.org/10.1073/pnas.1302581110\n" ,
   "----------------------------------------------------------------------------\n" ,
   "ZS Saad, RC Reynolds, HJ Jo, SJ Gotts, G Chen, A Martin, and RW Cox.\n" ,
   "  Correcting Brain-Wide Correlation Differences in Resting-State FMRI.\n" ,
   "  Brain Connectivity, 2013: 339-352.\n" ,
   "\n" ,
   "  * Just when you thought it was safe to go back into the waters of resting\n" ,
   "    state FMRI, another paper explaining why global signal regression is a\n" ,
   "    bad idea and a tentative step towards a different solution.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pubmed/23705677\n" ,
   "  * http://dx.doi.org/10.1089/brain.2013.0156\n" ,
   "----------------------------------------------------------------------------\n" ,
   "P Kundu, ND Brenowitz, V Voon, Y Worbe, PE Vertes, SJ Inati, ZS Saad,\n" ,
   "PA Bandettini, and ET Bullmore.\n" ,
   "  Integrated strategy for improving functional connectivity mapping using\n" ,
   "  multiecho fMRI.  PNAS 110: 16187-16192, 2013.\n" ,
   "\n" ,
   "  * A data acquistion and processing strategy for improving resting state FMRI.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3791700/\n" ,
   "  * http://dx.doi.org/10.1073/pnas.1301725110\n" ,
   "----------------------------------------------------------------------------\n" ,
   "PA Taylor and ZS Saad.\n" ,
   "  FATCAT: (An Efficient) Functional And Tractographic Connectivity Analysis\n" ,
   "  Toolbox.  Brain Connectivity 3:523-535, 2013.\n" ,
   "\n" ,
   "  * Introducing diffusion-based tractography tools in AFNI, with particular\n" ,
   "    emphases on complementing FMRI analysis and in performing interactive\n" ,
   "    visualization with SUMA.\n" ,
   "  * http://www.ncbi.nlm.nih.gov/pubmed/23980912\n" ,
   "  * http://dx.doi.org/10.1089/brain.2013.0154\n" ,
   "----------------------------------------------------------------------------\n" ,
   NULL } ;
#define NUM_afni_papers 238
