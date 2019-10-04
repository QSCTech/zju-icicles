// This is borrowed from rocket, and modified to be hardcoded to 32b.
// I will leave it as an excercise to the reader to make a parameterizable ALU
// that doesn't generate extra hardware for 32b. I also didn't carefully
// consider the function encodings. - Chris
package Sodor

import chisel3._
import chisel3.util._

import Common._
import Constants._

object ALU
{
  // TODO is this the optimal encoding?
  val SZ_ALU_FN = 5
  val ALU_X    = 0.U // TODO use a more optimal decode table, which uses "???" format
  val ALU_ADD  = 0.U
  val ALU_SLL  = 1.U
  val ALU_XOR  = 4.U
  val ALU_OR   = 6.U
  val ALU_AND  = 7.U
  val ALU_SRL  = 5.U
  val ALU_SUB  = 10.U
  val ALU_SRA  = 11.U
  val ALU_SLT  = 12.U
  val ALU_SLTU = 14.U
  val ALU_COPY1= 8.U

//---------------------------------------------------------------------------------------------------------------
  val ALU_MUL    = 2.U
  val ALU_MULH   = 3.U
  val ALU_MULHU  = 9.U
  val ALU_MULHSU = 13.U
  val ALU_DIV    = 18.U 
  val ALU_DIVU   = 15.U
  val ALU_REM    = 16.U
  val ALU_REMU   = 17.U
//---------------------------------------------------------------------------------------------------------------

  def isSub(cmd: UInt) = cmd(3)
  def isSLTU(cmd: UInt) = cmd(1)
}
import ALU._

class ALUIO(implicit val conf: SodorConfiguration) extends Bundle {
  val fn = Input(UInt(SZ_ALU_FN.W))
  val in2 = Input(UInt(conf.xprlen.W))
  val in1 = Input(UInt(conf.xprlen.W))
  val out = Output(UInt(conf.xprlen.W))
  val adder_out = Output(UInt(conf.xprlen.W))
}

class ALU(implicit val conf: SodorConfiguration) extends Module
{
  val io = IO(new ALUIO)

  val msb = conf.xprlen-1

  // ADD, SUB
  val sum = io.in1 + Mux(isSub(io.fn), -io.in2, io.in2)

  // SLT, SLTU
  val less  =  Mux(io.in1(msb) === io.in2(msb),sum(msb),
               Mux(isSLTU(io.fn),              io.in2(msb), 
                   io.in1(msb)
               ))

  require(conf.xprlen == 32)
  // SLL, SRL, SRA
  val shamt = io.in2(4,0).asUInt() //5 bit
  val shin_r = io.in1(31,0)
  val shin = Mux(io.fn === ALU_SRL  || io.fn === ALU_SRA, shin_r, Reverse(shin_r))
  val shout_r = (Cat(isSub(io.fn) & shin(msb), shin).asSInt() >> shamt)(msb,0) // connect and shift
  val shout_l = Reverse(shout_r)

  //---------------------------------------------------------------------------------------------------------------
  // MUL...
  val mul = io.in1 * io.in2
  val mulh =   ( ( (io.in1).asSInt() * (io.in2).asSInt() ) >> 32 ).asUInt()   
  val mulhu =  ( ( (io.in1) * (io.in2) ) >> 32 ).asUInt()
  val mulhsu = ( ( (io.in1).asSInt() * (io.in2) ) >> 32 ).asUInt()
    

  val in1_temp = Mux(io.in1(msb), -io.in1, io.in1)
  val in2_temp = Mux(io.in2(msb), -io.in2, io.in2)

  // DIV
  val div = // io.in2 == 0
            Mux((io.in2) === 0.U,                ~UInt(0,conf.xprlen),
            // io.in1 ^ io.in2 == 1
            Mux(~(io.in1(msb) ^ io.in2(msb)),   in1_temp / in2_temp,
            // io.in1 < 0 || io.in2 < 0
                                                 -(in1_temp / in2_temp) 
            ))            
  val divu = Mux(io.in2 === 0.U, ~UInt(0,conf.xprlen),io.in1 / io.in2)

  // REM
  val rem = // io.in2 == 0
            Mux((io.in2) === 0.U,   io.in1,
            // io.in1 < 0
            Mux((io.in1(msb)),      -(in1_temp % in2_temp),
            // io.in1 > 0
                                    in1_temp % in2_temp
            )) 
  val remu = Mux(io.in2 === 0.U, io.in1,io.in1 % io.in2)
  
  //---------------------------------------------------------------------------------------------------------------

  // ALU_COPY1
  val bitwise_logic =
    Mux(io.fn === ALU_AND, io.in1 & io.in2,
    Mux(io.fn === ALU_OR,  io.in1 | io.in2,
    Mux(io.fn === ALU_XOR, io.in1 ^ io.in2,
                           io.in1
        ))) 
 

  val out_xpr_length =
//---------------------------------------------------------------------------------------------------------------
    Mux(io.fn === ALU_REMU,                     remu, 
    Mux(io.fn === ALU_REM,                      rem,
    Mux(io.fn === ALU_DIVU,                     divu,
    Mux(io.fn === ALU_DIV,                      div,
    Mux(io.fn === ALU_MULHSU,                   mulhsu,
    Mux(io.fn === ALU_MULHU,                    mulhu,
    Mux(io.fn === ALU_MULH,                     mulh,
    Mux(io.fn === ALU_MUL,                      mul,        
//---------------------------------------------------------------------------------------------------------------
    Mux(io.fn === ALU_ADD || io.fn === ALU_SUB, sum,
    Mux(io.fn === ALU_SLT || io.fn === ALU_SLTU,less,   
    Mux(io.fn === ALU_SRL || io.fn === ALU_SRA, shout_r,
    Mux(io.fn === ALU_SLL,                      shout_l,
        bitwise_logic 
    ))))
    ))))))))


  io.out := out_xpr_length(31,0).asUInt()
  io.adder_out := sum
}
