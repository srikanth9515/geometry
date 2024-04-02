module Testbench;
    reg signed [7:0] A[0:1][0:1];
    reg signed [7:0] B[0:1][0:1];
    reg signed [7:0] C[0:1][0:1];
    wire signed [7:0] D[0:1][0:1];
    wire signed [7:0] E[0:1][0:1];
    wire signed [7:0] F[0:1][0:1];
    wire signed [7:0] subA_D[0:1][0:1];
    wire signed [7:0] subB_E[0:1][0:1];
    wire signed [7:0] subC_F[0:1][0:1];
    wire signed [7:0] AD_distance;
    wire signed [7:0] BE_distance;
    wire signed [7:0] CF_distance; 
    wire signed [7:0] tranresult1[0:1][0:1];
    wire signed [7:0] tranresult2[0:1][0:1];
    wire signed [7:0] tranresult3[0:1][0:1];
    wire signed [7:0] mul_AD[0:1][0:1];
    wire signed [7:0] mul_BE[0:1][0:1];
    wire signed [7:0] mul_CF[0:1][0:1];
    wire [7:0] median_AD;
    wire [7:0] median_BE;
    wire  [7:0] median_CF;

    Matsec m(
        .A(A),
        .B(B),
        .C(C),
        .D(D),
        .E(E),
        .F(F)
    );

    Matsub n(
        .A(A),
        .B(B),
        .C(C),
        .D(D),
        .E(E),
        .F(F),
        .subA_D(subA_D),
        .subB_E(subB_E),
        .subC_F(subC_F)
    );

    transposeMat o(
        .subA_D(subA_D),
        .subB_E(subB_E),
        .subC_F(subC_F),
        .tranresult1(tranresult1),
        .tranresult2(tranresult2),
        .tranresult3(tranresult3)
    );

    Matmul r(
        .tranresult1(tranresult1),
        .tranresult2(tranresult2),
        .tranresult3(tranresult3),
        .subA_D(subA_D),
        .subB_E(subB_E),
        .subC_F(subC_F),
        .mul_AD(mul_AD),
        .mul_BE(mul_BE),
        .mul_CF(mul_CF)
    );

    Matnorm p(
        .mul_AD(mul_AD),
        .mul_BE(mul_BE),
        .mul_CF(mul_CF),
        .median_AD(median_AD),
        .median_BE(median_BE),
        .median_CF(median_CF)
    );

    DistanceCalculator q(
        .A(A),
        .B(B),
        .C(C),
        .D(D),
        .E(E),
        .F(F),
        .AD_distance(AD_distance),
        .BE_distance(BE_distance),
        .CF_distance(CF_distance)
    );

   initial begin
         integer text;
         text = $fopen("output.txt", "w");
         
    // Provide values for A, B, and C
    A[0][0] =  1; // Example value
    A[0][1] = -1; // Example value
    B[0][0] = -4; // Example value
    B[0][1] =  6; // Example value
    C[0][0] = -3; // Example value
    C[0][1] = -5; // Example value
    
    #10;
    
    
        // Write the simulation results to the output file
        $fwrite(text, "AD_distance: %d\n", AD_distance);
        $fwrite(text, "BE_distance: %d\n", BE_distance);
        $fwrite(text, "CF_distance: %d\n", CF_distance);

        // Close the output file
        $fclose(text);
        
        $finish;
        
    end
endmodule

