`timescale 1ns / 1ps

//
// NOTE: This is a sample testbench, provided to you as a guidance.
//

module testbench_ballot(
    );

	reg [1:0] mode;
	reg [5:0] userID;
	reg [1:0] candidate; // 00:Air 01:Fire, 10:Earth, 11: Water
	reg clk;
	wire [1:0] ballotBoxId;
	wire [5:0] numberOfRegisteredVoters;
	wire [5:0] numberOfVotesWinner; // number of votes of winner
	wire [1:0] WinnerId;
	wire AlreadyRegistered;
	wire AlreadyVoted;
	wire NotRegistered;
	wire VotingHasNotStarted;
	wire RegistrationHasEnded;

	// Instantiate the Unit Under Test (UUT)
   SelectionOfAvatar uut(
		mode,
		userID,
		candidate,
		clk,
		ballotBoxId,
        numberOfRegisteredVoters,
        numberOfVotesWinner,
        WinnerId,
        AlreadyRegistered,
        AlreadyVoted,
        NotRegistered,
        VotingHasNotStarted,
        RegistrationHasEnded
	);

	// At 5, 15, 25, .. clk will change 0->1
	// At 10, 20, 30, .. clk will change 1->0
   	initial clk = 0;
	always #5 clk = ~clk;


	initial begin

		//... you may add your tests here


		$finish;

	end

endmodule
