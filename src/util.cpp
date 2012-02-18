/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  std::vector<variant> zip_vector(std::vector<variant> src, std::vector<variant> target) {
    std::vector<variant> result;
    for (int iSrc=0, iSrcEnd=(int)src.size(), iTargetSrc=(int)target.size(); iSrc<iSrcEnd && iSrc<iTargetSrc; ++iSrc) {
      std::vector<variant> row;
      row.push_back(src.at(iSrc));
      row.push_back(target.at(iSrc));
      result.push_back(row);
    }
    return result;
  }

  std::string join_vector(std::vector<std::string> v, const char *delimiter) {
    std::string result;
    for(size_t i=0,l=v.size(); i<l; i++) {
      if (v[i] == "") continue;
      if (result.size() > 0) result += delimiter;
      result += v[i];
    }
    return result;
  }

  const char * format_string(const std::string &fmt, ...) {
    int size=100;
    std::string str;
    va_list ap;
    while (1) {
      str.resize(size);
      va_start(ap, fmt);
      int n = vsnprintf((char *)str.c_str(), size, fmt.c_str(), ap);
      va_end(ap);
      if (n > -1 && n < size)
        return str.c_str();
      if (n > -1)
        size=n+1;
      else
        size*=2;
    }
  }

  std::string gsub_string(const std::string &sData, const std::string &sFrom, const std::string &sTo) {
    std::string sNew = sData;
    
    if (!sNew.empty()) {
      std::string::size_type toLen = sTo.length();
      std::string::size_type frLen = sFrom.length();
      std:: string::size_type loc = 0;
      
      while (std::string::npos != (loc = sNew.find(sFrom, loc))) {
        sNew.replace(loc, frLen, sTo);
        loc += toLen;
        
        if (loc >= sNew.length())
          break;
      }
    }
    return sNew;
  }

  nodes::SqlLiteral raw_sql(const char *sql) {
    return nodes::SqlLiteral(sql); 
  }
}