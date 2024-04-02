module Matsec(
  input signed [7:0] A[0:1][0:1],
  input signed [7:0] B[0:1][0:1],
  input signed [7:0] C[0:1][0:1],
  output reg signed [7:0] D[0:1][0:1],
  output reg signed [7:0] E[0:1][0:1],
  output reg signed [7:0] F[0:1][0:1]
);

always @* begin 
    D[0][0] = (A[0][0] + B[0][0])/2;
    D[0][1] = (A[0][1] + B[0][1])/2;
     
    E[0][0] = (B[0][0] + C[0][0])/2;
    E[0][1] = (B[0][1] + C[0][1])/2;
       
    F[0][0] = (C[0][0] + A[0][0])/2;
    F[0][1] = (C[0][1] + A[0][1])/2;
end
endmodule




module Matsub (
    input signed [7:0] A[0:1][0:1],
    input signed [7:0] B[0:1][0:1],
    input signed [7:0] C[0:1][0:1],
    input signed [7:0] D[0:1][0:1],
    input signed [7:0] E[0:1][0:1],
    input signed [7:0] F[0:1][0:1],
  output reg signed [7:0] subA_D[0:1][0:1],
  output reg signed [7:0] subB_E[0:1][0:1],
  output reg signed [7:0] subC_F[0:1][0:1]
  );
always @* begin
        subA_D[0][0] = A[0][0] - D[0][0];
        subA_D[0][1] = A[0][1] - D[0][1];
        
        subB_E[0][0] = B[0][0] - E[0][0];
        subB_E[0][1] = B[0][1] - E[0][1];
        
        subC_F[0][0] = C[0][0] - F[0][0];
        subC_F[0][1] = C[0][1] - F[0][1];
end
endmodule

module transposeMat(
  input signed [7:0] subA_D[0:1][0:1],
  input signed [7:0] subB_E[0:1][0:1],
  input signed [7:0] subC_F[0:1][0:1],
  output reg signed [7:0] tranresult1[0:1][0:1],
  output reg signed [7:0] tranresult2[0:1][0:1],
  output reg signed [7:0] tranresult3[0:1][0:1]
);
integer i, j;
always @* begin
 for(i=0;i<2;i=i+1) begin
  for(j=0;j<2;j=j+1) begin
    tranresult1[i][j] = subA_D[j][i];
    tranresult2[i][j] = subB_E[j][i];
    tranresult3[i][j] = subC_F[j][i];
  end
 end
end
endmodule





module Matmul(
    input signed [7:0] tranresult1[0:1][0:1],
    input signed [7:0] tranresult2[0:1][0:1],
    input signed [7:0] tranresult3[0:1][0:1],
    input signed [7:0] subA_D[0:1][0:1],
    input signed [7:0] subB_E[0:1][0:1],
    input signed [7:0] subC_F[0:1][0:1],
    
   output reg signed [7:0] mul_AD[0:1][0:1],
   output reg signed [7:0] mul_BE[0:1][0:1],
   output reg signed [7:0] mul_CF[0:1][0:1]
);
integer i,j;
always @* begin
   for(i=0;i<2;i=i+1) begin
  for(j=0;j<2;j=j+1) begin
  mul_AD[0][0]=tranresult1[0][0]*subA_D[0][0]+tranresult1[1][0]*subA_D[0][1];
  mul_BE[0][0]=tranresult2[0][0]*subB_E[0][0]+tranresult2[1][0]*subB_E[0][1];
  mul_CF[0][0]=tranresult3[0][0]*subC_F[0][0]+tranresult3[1][0]*subC_F[0][1];
   end
end 
end 
endmodule






module Matnorm (
    input signed [7:0] mul_AD[0:1][0:1],
    input signed [7:0] mul_BE[0:1][0:1],
    input signed [7:0] mul_CF[0:1][0:1],
    output reg [7:0] median_AD,
    output reg [7:0] median_BE,
    output reg [7:0] median_CF
);
// Declare the square root function
function [15:0] sqrt;
    input [15:0] x;
    begin
        sqrt = $sqrt(x);
    end
endfunction

// Compute distances
always @* begin
    // Distance between A and D
    median_AD = sqrt(mul_AD[0][0]);
    // Distance between B and E
    median_BE = sqrt(mul_BE[0][0]);
    // Distance between C and F
   median_CF = sqrt(mul_CF[0][0]);
end

endmodule




module DistanceCalculator (
    input signed [7:0] A[0:1][0:1],
    input signed [7:0] B[0:1][0:1],
    input signed [7:0] C[0:1][0:1],
    input signed [7:0] D[0:1][0:1],
    input signed [7:0] E[0:1][0:1],
    input signed [7:0] F[0:1][0:1],
    output reg [7:0] AD_distance,
    output reg [7:0] BE_distance,
    output reg [7:0] CF_distance
);



// Declare the square root function
function [15:0] sqrt;
    input [15:0] x;
    begin
        sqrt = $sqrt(x);
    end
endfunction

// Compute distances
always @* begin
    // Distance between A and D
    AD_distance = sqrt((D[0][0] - A[0][0])*(D[0][0] - A[0][0]) + (D[0][1] - A[0][1])*(D[0][1] - A[0][1]));
    // Distance between B and E
    BE_distance = sqrt((E[0][0] - B[0][0])*(E[0][0] - B[0][0]) + (E[0][1] - B[0][1])*(E[0][1] - B[0][1]));
    // Distance between C and F
    CF_distance = sqrt((F[0][0] - C[0][0])*(F[0][0] - C[0][0]) + (F[0][1] - C[0][1])*(F[0][1] - C[0][1]));
end

endmodule

