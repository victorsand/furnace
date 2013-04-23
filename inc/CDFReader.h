/*
 * CDFReader.h
 *
 *  Created on: Apr 5, 2013
 *      Author: Victor Sand
 *
 *  Base class for various readers. Each specific model needs its own
 *  subclass and implementation of Read(). The idea is to always write
 *  to a uniform VDF format. When adding new features to the VDF format,
 *  make sure to provide default values so that old readers do not break.
 *
 */

#ifndef CDFREADER_H_
#define CDFREADER_H_

#include <string>
#include <vector>

namespace ccmc {
	class Kameleon;
	class Interpolator;
}

namespace osp
{

class VDFData;

class CDFReader
{
public:
  virtual ~CDFReader();
	// Read a whole folder with CDF files. Def. imlementation may be overridden.
	virtual bool ReadFolder(); 
	virtual void SetPath(const std::string &_path);
	// Read an indivudual file. Subclasses must provide implementation.
  virtual bool ReadFile(const std::string &_inFilename,
	                      unsigned int _timestep) = 0;
  // Accessors
  VDFData * DataObject() { return dataObject_; }
  bool HasRead() const { return hasRead_; }
protected:
  // Constructor, takes care of VDFDataObject initialization
  CDFReader();
  // Data members
	std::string path_;
  std::vector<std::string> variableNames_; // support combinations of variables
  VDFData * dataObject_;
  bool hasRead_; // Remember to have Read() implementations set this

	// CCMC parts
	ccmc::Kameleon *kameleon_;
	ccmc::Interpolator *interpolator_;
};

}

#endif
