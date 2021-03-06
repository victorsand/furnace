/*
 * Author: Victor Sand (victor.sand@gmail.com);
 *
 * Base class for reading and writing volume data. The function
 * ProcessFolder() needs to be implemented in subclasses, and the standard 
 * Write() function may be overridden if specializations are needed.
 * 
 * ProcessFolder() reads a folder with one or more files of source data.
 *
 * Note that this class also defines the file format!
 *
 */

#ifndef VOLUMEPROCESSOR_H_
#define VOLUMEPROCESSOR_H_

#include <string>
#include <vector>

#define _FILE_OFFSET_BITS 64
#define off off64_t

namespace osp {

class VolumeProcessor {
public:

  virtual ~VolumeProcessor();

  virtual bool ProcessFolder(const std::string &_sourceFolder,
                             const std::string &_destFolder) = 0;

  void SetDimensions(unsigned int _xDim,
                     unsigned int _yDim,
                     unsigned int _zDim);

  // 0 for cartesian
  // 1 for spherical
  void SetGridType(unsigned int _gridType);

protected:
  VolumeProcessor();
  VolumeProcessor(const VolumeProcessor&);

  // Write (temporary) header
  bool WriteHeader(const std::string &_destFolder);

  // Gather values from temporary files, normalize and write
  // to single output file
  bool WriteFinal(const std::string &_destFolder);

  // Delete temporary files
  bool DeleteTempFiles(const std::string &_destFolder);

  // Names for (temporary) header and timestep files
  const std::string tempSuffix_ = ".tmp";
  const std::string headerFilename_ = "header";
  const std::string headerSuffix_ = ".tmp";
  const std::string timestepFilename_ = "timestep_";
  const std::string timestepSuffix_ = ".tmp";
  
  // Name for final file
  const std::string finalFilename = "volume.vdf";

  // Data to write
  unsigned int gridType_; 
  unsigned int numTimesteps_;
  unsigned int xDim_;
  unsigned int yDim_;
  unsigned int zDim_;

  // Stores data in one time step before writing to disk
  std::vector<float> data_;

  // Num voxels for one frame
  unsigned int numVoxelsPerTimestep_;

  // For normalization step 
  float min_;
  float max_;
  
  // State
  bool hasRead_;
};

} // namespace

#endif
