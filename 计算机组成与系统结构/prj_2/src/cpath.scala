//**************************************************************************
// RISCV Processor Control Path
//--------------------------------------------------------------------------
//
// cpath must check io.imem.resp.valid to verify it's decoding an actual
// instruction. Otherwise, it is in charge of muxing off ctrl signals.

package Sodor
{

import chisel3._
import chisel3.util._


import Common._
import Common.Instructions._
import Constants._
import ALU._

class CtrlSignals extends Bundle()
{
   val exe_kill  = Output(Bool())    // squash EX stage (exception/mret occurred)
   val pc_sel    = Output(UInt(3.W))
   val brjmp_sel = Output(Bool())
   val op1_sel   = Output(UInt(2.W))
   val op2_sel   = Output(UInt(2.W))
   val alu_fun   = Output(UInt(SZ_ALU_FN.W))
   val wb_sel    = Output(UInt(2.W))
   val rf_wen    = Output(Bool())
   val bypassable = Output(Bool())     // instruction's result can be bypassed
   val csr_cmd   = Output(UInt(CSR.SZ))

   val dmem_val  = Output(Bool())
   val dmem_fcn  = Output(UInt(M_X.getWidth.W))
   val dmem_typ  = Output(UInt(3.W))

   val exception = Output(Bool())
}

class CpathIo(implicit val conf: SodorConfiguration) extends Bundle()
{
   val dcpath = Flipped(new DebugCPath())
   val imem = Flipped(new FrontEndCpuIO())
   val dmem = new MemPortIo(conf.xprlen)
   val dat  = Flipped(new DatToCtlIo())
   val ctl  = new CtrlSignals()
   override def clone = { new CpathIo().asInstanceOf[this.type] }
}


class CtlPath(implicit val conf: SodorConfiguration) extends Module
{
   val io = IO(new CpathIo())
   io := DontCare
                             //
                             //   inst val?                                                                                mem flush/sync
                             //   |    br type                      alu fcn                 bypassable?                    |
                             //   |    |     is jmp?                |        wb sel         |  mem en               csr cmd|
                             //   |    |     |  op1 sel  op2 sel    |        |       rf wen |  |      mem cmd       |      |
   val csignals =            //   |    |     |  |        |          |        |       |      |  |      |      mask type     |
      ListLookup(io.imem.resp.bits.inst,//   |  |        |          |        |       |      |  |      |      |      |      |
                             List(N, BR_N  , N, OP1_X  , OP2_X   , ALU_X   , WB_X,   REN_0, N, MEN_0, M_X  , MT_X,  CSR.N, M_N),
               Array(       //
                  LW      -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_ADD , WB_MEM, REN_1, N, MEN_1, M_XRD, MT_W,  CSR.N, M_N),
                  LB      -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_ADD , WB_MEM, REN_1, N, MEN_1, M_XRD, MT_B,  CSR.N, M_N),
                  LBU     -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_ADD , WB_MEM, REN_1, N, MEN_1, M_XRD, MT_BU, CSR.N, M_N),
                  LH      -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_ADD , WB_MEM, REN_1, N, MEN_1, M_XRD, MT_H,  CSR.N, M_N),
                  LHU     -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_ADD , WB_MEM, REN_1, N, MEN_1, M_XRD, MT_HU, CSR.N, M_N),
                  SW      -> List(Y, BR_N  , N, OP1_RS1, OP2_IMS , ALU_ADD , WB_X  , REN_0, N, MEN_1, M_XWR, MT_W,  CSR.N, M_N),
                  SB      -> List(Y, BR_N  , N, OP1_RS1, OP2_IMS , ALU_ADD , WB_X  , REN_0, N, MEN_1, M_XWR, MT_B,  CSR.N, M_N),
                  SH      -> List(Y, BR_N  , N, OP1_RS1, OP2_IMS , ALU_ADD , WB_X  , REN_0, N, MEN_1, M_XWR, MT_H,  CSR.N, M_N),

                  AUIPC   -> List(Y, BR_N  , N, OP1_IMU, OP2_PC  , ALU_ADD  ,WB_ALU, REN_1, Y, MEN_0, M_X ,  MT_X,  CSR.N, M_N),
                  LUI     -> List(Y, BR_N  , N, OP1_IMU, OP2_X   , ALU_COPY1,WB_ALU, REN_1, Y, MEN_0, M_X ,  MT_X,  CSR.N, M_N),

                  ADDI    -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_ADD , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  ANDI    -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_AND , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  ORI     -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_OR  , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  XORI    -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_XOR , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SLTI    -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_SLT , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SLTIU   -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_SLTU, WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SLLI    -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_SLL , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SRAI    -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_SRA , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SRLI    -> List(Y, BR_N  , N, OP1_RS1, OP2_IMI , ALU_SRL , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),

                  SLL     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_SLL , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  ADD     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_ADD , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SUB     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_SUB , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SLT     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_SLT , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SLTU    -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_SLTU, WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  AND     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_AND , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  OR      -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_OR  , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  XOR     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_XOR , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SRA     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_SRA , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  SRL     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_SRL , WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
               //---------------------------------------------------------------------------------------------------------------
                  MUL     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_MUL ,   WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  MULH    -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_MULH,   WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  MULHU   -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_MULHU,  WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),                  
                  MULHSU  -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_MULHSU, WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),                  
                  
                  DIV     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_DIV ,   WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),                  
                  DIVU    -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_DIVU,   WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),                  
                  
                  REM     -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_REM ,   WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),                  
                  REMU    -> List(Y, BR_N  , N, OP1_RS1, OP2_RS2 , ALU_REMU,   WB_ALU, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),                                    
               //---------------------------------------------------------------------------------------------------------------
                  JAL     -> List(Y, BR_J  , Y, OP1_X  , OP2_X   , ALU_X   , WB_PC4, REN_1, Y, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  JALR    -> List(Y, BR_JR , Y, OP1_RS1, OP2_IMI , ALU_X   , WB_PC4, REN_1, N, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  BEQ     -> List(Y, BR_EQ , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  BNE     -> List(Y, BR_NE , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  BGE     -> List(Y, BR_GE , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  BGEU    -> List(Y, BR_GEU, N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  BLT     -> List(Y, BR_LT , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.N, M_N),
                  BLTU    -> List(Y, BR_LTU, N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.N, M_N),

                  CSRRWI  -> List(Y, BR_N  , N, OP1_IMZ, OP2_X   , ALU_COPY1,WB_CSR, REN_1, N, MEN_0, M_X ,  MT_X,  CSR.W, M_N),
                  CSRRSI  -> List(Y, BR_N  , N, OP1_IMZ, OP2_X   , ALU_COPY1,WB_CSR, REN_1, N, MEN_0, M_X ,  MT_X,  CSR.S, M_N),
                  CSRRW   -> List(Y, BR_N  , N, OP1_RS1, OP2_X   , ALU_COPY1,WB_CSR, REN_1, N, MEN_0, M_X ,  MT_X,  CSR.W, M_N),
                  CSRRS   -> List(Y, BR_N  , N, OP1_RS1, OP2_X   , ALU_COPY1,WB_CSR, REN_1, N, MEN_0, M_X ,  MT_X,  CSR.S, M_N),
                  CSRRC   -> List(Y, BR_N  , N, OP1_RS1, OP2_X   , ALU_COPY1,WB_CSR, REN_1, N, MEN_0, M_X ,  MT_X,  CSR.C, M_N),
                  CSRRCI  -> List(Y, BR_N  , N, OP1_IMZ, OP2_X   , ALU_COPY1,WB_CSR, REN_1, N, MEN_0, M_X ,  MT_X,  CSR.C, M_N),
                                                                                                                                  // TODO:
                  ECALL   -> List(Y, BR_N  , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.I, M_FD), // don't think I actually
                  MRET    -> List(Y, BR_N  , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.I, M_FD), // need to flush memory here
                  DRET    -> List(Y, BR_N  , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.I, M_FD),
                  EBREAK  -> List(Y, BR_N  , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.I, M_FD),
                  WFI     -> List(Y, BR_N  , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.I, M_FD),

                  FENCE_I -> List(Y, BR_N  , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_0, M_X  , MT_X,  CSR.N, M_SI),
                  FENCE   -> List(Y, BR_N  , N, OP1_X  , OP2_X   , ALU_X   , WB_X  , REN_0, N, MEN_1, M_X  , MT_X,  CSR.N, M_SD)
                  // we are already sequentially consistent, so no need to honor the fence instruction
                  ))

   // Put these control signals in variables
   val (cs_inst_val: Bool) :: cs_br_type :: cs_brjmp_sel      :: cs_op1_sel            :: cs_op2_sel  :: cs0 = csignals
   val cs_alu_fun          :: cs_wb_sel  :: (cs_rf_wen: Bool) :: (cs_bypassable: Bool) ::                cs1 = cs0
   val (cs_mem_en: Bool)   :: cs_mem_fcn :: cs_msk_sel        :: cs_csr_cmd            :: cs_sync_fcn :: Nil = cs1


   // Is the instruction valid? If not, mux off all control signals!
   val ctrl_valid = io.imem.resp.valid

   // Branch Logic
   val take_evec = Wire(Bool()) // jump to the csr.io.evec target
                          // (for exceptions or sret, taken in the WB stage)

   val ctrl_pc_sel = Mux(take_evec            ,  PC_EXC,
                     Mux(cs_br_type === BR_N  ,  PC_4,
                     Mux(cs_br_type === BR_NE ,  Mux(!io.dat.br_eq,  PC_BR, PC_4),
                     Mux(cs_br_type === BR_EQ ,  Mux( io.dat.br_eq,  PC_BR, PC_4),
                     Mux(cs_br_type === BR_GE ,  Mux(!io.dat.br_lt,  PC_BR, PC_4),
                     Mux(cs_br_type === BR_GEU,  Mux(!io.dat.br_ltu, PC_BR, PC_4),
                     Mux(cs_br_type === BR_LT ,  Mux( io.dat.br_lt,  PC_BR, PC_4),
                     Mux(cs_br_type === BR_LTU,  Mux( io.dat.br_ltu, PC_BR, PC_4),
                     Mux(cs_br_type === BR_J  ,  PC_J,
                     Mux(cs_br_type === BR_JR ,  PC_JR,
                     PC_4
                     ))))))))))

   io.imem.req.valid := !(ctrl_pc_sel === PC_4) && ctrl_valid

   io.ctl.exe_kill   := take_evec
   io.ctl.pc_sel     := ctrl_pc_sel
   io.ctl.brjmp_sel  := cs_brjmp_sel.toBool
   io.ctl.op1_sel    := cs_op1_sel
   io.ctl.op2_sel    := cs_op2_sel
   io.ctl.alu_fun    := cs_alu_fun
   io.ctl.wb_sel     := cs_wb_sel
   io.ctl.rf_wen     := Mux(!ctrl_valid, false.B, cs_rf_wen.toBool)
   io.ctl.bypassable := cs_bypassable.toBool

   val rs1_addr = io.imem.resp.bits.inst(RS1_MSB, RS1_LSB)
   val csr_ren = (cs_csr_cmd === CSR.S || cs_csr_cmd === CSR.C) && rs1_addr === 0.U
   val csr_cmd = Mux(csr_ren, CSR.R, cs_csr_cmd)
   io.ctl.csr_cmd    := Mux(!ctrl_valid, CSR.N, csr_cmd)

   // Memory Requests
   if(NUM_MEMORY_PORTS == 1)
      io.ctl.dmem_val   := cs_mem_en.toBool && ctrl_valid && !take_evec
   else
      io.ctl.dmem_val   := cs_mem_en.toBool && ctrl_valid
   io.ctl.dmem_fcn   := cs_mem_fcn
   io.ctl.dmem_typ   := cs_msk_sel


   //-------------------------------
   // Exception Handling
   io.ctl.exception := !cs_inst_val && io.imem.resp.valid
   take_evec        := RegNext(io.ctl.exception) || io.dat.csr_eret


}

}
