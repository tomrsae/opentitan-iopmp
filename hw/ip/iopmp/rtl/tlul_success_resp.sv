`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/18/2024 12:59:25 PM
// Design Name: 
// Module Name: tlul_success_resp
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: Dummy successful response generator. If ERR_CFG registers signals(rwe or rre) is set, this response will be sent to a master.
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
import top_pkg::*;
import tlul_pkg::*;
import config_pkg::*;
import iopmp_pkg::*;


module tlul_success_resp(
    input                                   clk,
    input                                   rst,
    input  tlul_pkg::tl_h2d_t               req_i,
    output tlul_pkg::tl_d2h_t               rsp_o
);

logic  rsp_pending;
logic [SourceWidth - 1 : 0]          rsp_source;
tl_a_op_e                            rsp_opcode;

always_ff @(posedge clk) begin
    if (rst) begin
      rsp_pending       <= 1'b0;
      rsp_source        <= {top_pkg::TL_AIW{1'b0}};
      rsp_opcode        <= Get;
      //rsp_size        <= '0;
    end else if (rsp_pending && req_i.d_ready) begin
      rsp_pending       <= 1'b0;
    end else if (req_i.a_valid && rsp_o.a_ready) begin
      rsp_pending       <= 1'b1;
      rsp_source        <= req_i.a_source;
      rsp_opcode        <= req_i.a_opcode;
      //rsp_size        <= tl_h_i.a_size;
    end
end

assign rsp_o.a_ready  = ~rsp_pending;
assign rsp_o.d_valid  = rsp_pending;

assign rsp_o.d_source = rsp_source;
assign rsp_o.d_sink   = 8'hAA;
assign rsp_o.d_param  = '0;
assign rsp_o.d_size   = 2'b10;
assign rsp_o.d_opcode = (rsp_opcode == Get) ? AccessAckData : AccessAck;
assign rsp_o.d_data   = '1;
assign rsp_o.d_error  = 1'b0;
    
endmodule
