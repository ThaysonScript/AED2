all:
	mkdir -p inputs
	mkdir -p outputs
	reset; gcc *.c -o main; 
	./main < inputs/mil_linhas.in > outputs/output_mil_linhas.out && wait
	./main < inputs/dez_mil_linhas.in > outputs/output_dez_mil_linhas.out && wait
	./main < inputs/cem_mil_linhas.in > outputs/output_cem_mil_linhas.out && wait
	./main < inputs/um_milhao_linhas.in > outputs/output_um_milhao_linhas.out && wait
	# ./main < inputs/dez_milhoes_linhas.in > outputs/output_dez_milhoes_linhas.out