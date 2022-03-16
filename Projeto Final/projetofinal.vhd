library IEEE;  
	use IEEE.std_logic_1164.all; 
	use ieee.std_logic_unsigned.all;
	use ieee.numeric_std.all;

	ENTITY projetofinal IS
		PORT(
			clk, m1, m2, m3, m4, m5       : IN   STD_LOGIC; -- bits de moeda
			sel1, sel2, sel3, sel4        : IN   STD_LOGIC; -- seleciona o refrigerante
			confirma    : IN   STD_LOGIC;   
			sum5, sum10, sum25, sum50, sum100, refri1, refri2, refri3, refri4 : inout std_LOGIC);
	END projetofinal;

	ARCHITECTURE project_architecture OF projetofinal IS
		signal p1   : std_LOGIC_VECTOR(7 downto 0); -- := "00010100";  --preco do refrigerante 1 = 100 centavos / 20
		signal p2   : std_LOGIC_VECTOR(7 downto 0);  --:= "00100010";  --preco do refrigerante 2 = 170 centavos / 34
		signal p3   : std_LOGIC_VECTOR(7 downto 0);  --:= "00101101";  --preco do refrigerante 3 = 225 centavos / 45
		signal p4   : std_LOGIC_VECTOR(7 downto 0);  --:= "00110010";  --preco do refrigerante 4 = 250 centavos / 50
		                                                               --OBS: Fizemos uma conversão em que 5 centavos = 1 em binário, a fim de aumentar a capacidade de armazenamento
		signal sum  : std_LOGIC_VECTOR(7 downto 0) := "00000000";  --registrador que guarda o valor do saldo corrente
		signal valor: std_LOGIC_VECTOR(7 downto 0) := "00000000"; --proximo valor a ser somado
		signal sig_m1, sig_m2, sig_m3, sig_m4, sig_m5: std_logic; -- os sinais sig_m1 .. sig_m5 são usados para detectar a borda de subida nos botões de moeda
		signal moeda: std_logic;  -- moeda é o bit que detecta uma nova moeda
		
	BEGIN
		 p1 <= "00010100"; -- os registradores de preço recebem seus dados
		 p2 <= "00100010";
		 p3 <= "00101101";
		 p4 <= "00110010";

		PROCESS (clk) 
		BEGIN
		
			if(rising_edge(clk)) then
			
				if(m1 = '1' AND sig_m1 = '0') then	-- testa se o botão de moeda 1 for pressionado	
					valor <= "00000001";					-- como sig_m1..sig_m5 recebem o valor de m1..m5 no próximo ciclo de clock, a soma será feita apenas uma vez
					moeda <= '1';							-- valor recebe 5 centavos
					sum5  <= '1';
					
				elsif(m2 = '1' AND sig_m2 = '0') then -- testa moeda 2
					valor <= "00000010";
					moeda <= '1';
					sum10 <= '1';
					
				elsif(m3 = '1' AND sig_m3 = '0') then -- testa moeda 3
					valor <= "00000101";
					moeda <= '1';
					sum25 <= '1';
					
				elsif(m4 = '1' AND sig_m4 = '0') then -- testa moeda 4
				   valor <= "00001010";
					moeda <= '1';
					sum50 <= '1';
					
				elsif(m5 = '1' AND sig_m5 = '0') then -- testa moeda 5
					valor  <= "00010100";
					moeda  <= '1';
					sum100 <= '1';
						
				elsif(moeda = '1') then					-- se for detectado moeda, realiza  uma soma
					sum   <= sum + valor;
					moeda <= '0';
					
					
				elsif(sel1 = '1' and sum >= p1) then -- caso o usuário selecione o refrigerante 1 e o saldo for maior ou igual o preço
					refri1 <= '1';							 -- saída de refri 1 recebe 1.
					
				elsif(sel2 = '1' and sum >= p2) then -- refri 2...
					refri2 <= '1';
					
				elsif(sel3 = '1' and sum >= p3) then -- refri 3...
					refri3 <= '1';
					
				elsif(sel4 = '1' and sum >= p4) then -- refri 4...
					refri4 <= '1';
                    
						  
				elsif(refri1 = '1' OR refri2 = '1' OR refri3 = '1' OR refri4 = '1') then -- quando a máquina fornece um refrigerante
					if(confirma = '1') then																 -- espera o usuário apertar o botão de confirma
					refri1 <= '0'; -- zera as saídas de refrigerante
					refri2 <= '0';
					refri3 <= '0';
					refri4 <= '0';
					sum    <= "00000000"; -- zera o registrador de saldo
					else null;
					end if;
					
					
				elsif(sum5 = '1' OR sum10 = '1' OR sum25 = '1' OR sum50 = '1' OR sum100 = '1') then -- testa se algum dos botões foi apertado
					sum5   <= '0'; -- zera no próximo ciclo
					sum10  <= '0';
					sum25  <= '0';
					sum50  <= '0';
					sum100 <= '0';

				else null;
					
				end if;
			sig_m1 <= m1; -- os sinais sig_m1 .. sig_m5 recebem m1..m5 para garantir que no próximo ciclo a soma não seja feita novamente
			sig_m2 <= m2;
			sig_m3 <= m3;
			sig_m4 <= m4;
			sig_m5 <= m5;
			end if;
		end process;
	end project_architecture;