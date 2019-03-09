/*
 * Copyright (C) 2006-2016  Music Technology Group - Universitat Pompeu Fabra
 *
 * This file is part of Essentia
 *
 * Essentia is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation (FSF), either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the Affero GNU General Public License
 * version 3 along with this program.  If not, see http://www.gnu.org/licenses/
 */

// Streaming extractor designed for analysis of music collections
#include "streaming_extractor_music.h"

using namespace std;
using namespace essentia;
using namespace essentia::streaming;
using namespace essentia::scheduler;

int audioAnalysisFromFile(string audioFilename, string outputFilename, string profileFilename) {
  // Returns: 1 on essentia error
  //          2 if there are no tags in the file
  int result;
  try {
    essentia::init();

    cout.precision(10); // TODO ????

    MusicExtractor *extractor = new MusicExtractor();

    extractor->setExtractorOptions(profileFilename);
    extractor->mergeValues(extractor->results);

    result = extractor->compute(audioFilename);

    if (result > 0) {
        cerr << "Quitting early." << endl;
    } else {
        extractor->outputToFile(extractor->stats, outputFilename);
        if (extractor->options.value<Real>("outputFrames")) {
          extractor->outputToFile(extractor->results, outputFilename+"_frames");
        }
    }
    /* print all theinterested values ...danceability ....  extractor->results->highlevel->danceability->value*/
    cerr << &(extractor->results.getRealPool()) << endl;
    essentia::shutdown();
  }
  catch (EssentiaException& e) {
    cerr << e.what() << endl;
    return 1;
  }
  return result;

}
