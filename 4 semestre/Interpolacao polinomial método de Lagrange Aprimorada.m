function F_lagrange(x, y, p)
    
    % Verifica se os vetores x e y são do mesmo tamanho 
    if ~isvector(x) || ~isvector(y) || length(x) ~= length(y) 
        disp("Os vetores x e y devem ser vetores do mesmo tamanho.");
        return;
    end 
    % Verifica se p é um valor numérico 
    if ~isnumeric(p) 
        disp("O ponto p deve ser um valor numérico."); 
        return;
    end
    
    X = sym('X');
    n = length(x);   
    % sL = zeros(size(p)); Linha reduntante
    
    Fp = 0;
    %Fn = 0; Linha reduntante, é desnecessaria pois podemos utilizar o polinômio para calcular o valor em p 
    
    for i = 1:n
        %Li = ones(size(p)); Linha reduntante, é desnecessaria pois podemos utilizar o polinômio para calcular o valor em p 
        L = 1;
        for j = 1:n
            if j ~= i
                L = L * (X - x(j)) / (x(i) - x(j));
                %Li = Li * (p - x(j)) / (x(i) - x(j)); Linha reduntante, é desnecessaria pois podemos utilizar o polinômio para calcular o valor em p
            end
        end
        Fp = Fp + y(i) * L;
        %Fn = Fn + y(i) * Li; Linha reduntante, é desnecessaria pois podemos utilizar o polinômio para calcular o valor em p
    end
    
    disp("Seu polinômio é:");
    Fp = simplify(Fp);
    disp(Fp);

    lagrange_func = matlabFunction(Fp); % Foi montado a função antes para usar ela para mostar o valor em p
    f_p = double(lagrange_func(p)); % Foi calculado o valor de p antes
    
    % Verifica se o ponto p está no intervalo dos dados fornecidos 
    if p < min(x) || p > max(x) 
        warning('O ponto p está fora do intervalo dos pontos conhecidos.'); 
    end
    
    fprintf("O valor aproximado no ponto p = %.2f é: %.2f\n", p, f_p);

    x_plot = linspace(min(x), max(x), 1000);
    y_plot = lagrange_func(x_plot);
    
    figure;
    plot(x_plot, y_plot, 'b-', 'LineWidth', 2); 
    hold on;
    plot(x, y, 'ro', 'MarkerFaceColor', 'r', 'MarkerSize', 4);
    plot(p, f_p, 'gs', 'MarkerFaceColor', 'g', 'MarkerSize', 4);
    title('Interpolação Polinomial de Lagrange');
    xlabel('x');
    ylabel('f(x)');
    legend('Polinômio interpolador', 'Pontos conhecidos', sprintf('Ponto interpolado (p = %.2f)', p), 'Location', 'northeast');
    
    % No octave online a opção best não é nativa, então uma solução para resolver o warning que ocorre no compilador online, é substituir o "best" por "northeast".
    % Antigo: " legend('Polinômio interpolador', 'Pontos conhecidos', sprintf('Ponto interpolado (p = %.2f)', p), 'Location', 'Best'); "
    grid on;
    hold off;
end