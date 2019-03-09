#ifndef _STREAMING_EXTRACTOR_MUSIC
#define _STREAMING_EXTRACTOR_MUSIC

#include <essentia/streaming/algorithms/poolstorage.h>
#include <essentia/essentiautil.h>

#include "extractor_music/MusicExtractor.h"
#include "credit_libav.h"
#include "../constants.h"

int audioAnalysisFromFile(string audioFilename, string outputFilename, string profileFilename);

#endif