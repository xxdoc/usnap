
#ifndef __BITIO_H

#define __BITIO_H

#include <stdio.h>

struct BIT_FILE {
  FILE *file;
  unsigned char mask;
  int rack;
  int pacifier_counter;
};

#ifdef __STDC__
  BIT_FILE *OpenInputBitFile (char *name);
  BIT_FILE *OpenOutputBitFile (char *name);
  void OutputBit (BIT_FILE *bit_file, int bit);
  void OutputBits (BIT_FILE *bit_file, unsigned long code, int count);
  int InputBit (BIT_FILE *bit_file);
  unsigned long InputBits (BIT_FILE *bit_file, int bit_count);
  void CloseInputBitFile (BIT_FILE *bit_file);
  void CloseOutputBitFile (BIT_FILE *bit_file);
  void FilePrintBinary (FILE *file, unsigned int code, int bits);
#else
  BIT_FILE *OpenInpuBitFile ();
  BIT_FILE *OpenOutputBitFile ();
  void OutputBit();
  void OutputBits();
  int InputBit();
  unsigned long InputBits();
  void CloseInputBitFile();
  void CloseOutputBitFile();
  void FilePrintBinary();
#endif

#endif	// __BITIO_H
