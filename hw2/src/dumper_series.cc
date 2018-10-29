#include "dumper_series.hh"


DumperSeries::DumperSeries(std::unique_ptr<Series>& series_inp):
  series{series_inp},
  precision{4}
  {};
/*-----------------------------------------------------*/

void DumperSeries::setPrecision(Uint new_precision){
  this->precision = new_precision ;
}

/*-----------------------------------------------------*/
void DumperSeries::setSeperator(std::string seperator){
    if(seperator == ","){
      this->seperator = seperator;
      //this->file_ending = ".csv";
    }
    else if(seperator == " "){
      this->seperator = seperator;
      //this->file_ending = ".txt";
    }
    else if(seperator == "|"){
      this->seperator = seperator;
      //this->file_ending = ".psv";
    }
    else {
      std::cerr << "Invalid seperator: " << seperator << std::endl;
    }
}
