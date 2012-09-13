% This function processes the derived data from
% davinci_block_search_derive_data() and plots it

function [] = block_search_make_plots(platformName, gridDim, graphVector, upperLimitVector, boundaries, averageOrIndividualIterationGraphs)
    numIterations = 4;
    cacheBlockDimMin = 4;
    numGraphs = size(graphVector, 2);
    xCacheBlockSizes = log2(gridDim) - log2(cacheBlockDimMin) + 1;
    yCacheBlockSizes = log2(gridDim) - log2(cacheBlockDimMin) + 1;

    [derivedData] = block_search_derive_data(platformName, gridDim, cacheBlockDimMin, numIterations, boundaries);
    [platform] = platform_info(platformName);
    
    if (boundaries == 'c')
        boundaryType = 'Const.';
    elseif (boundaries == 'p')
        boundaryType = 'Per.';
    end
    
    % plot data
    close all;

    for i = 1:(xCacheBlockSizes+1)
        xAxisLabels{i} = int2str(cacheBlockDimMin * 2^(i-1));
    end

    for j = 1:(yCacheBlockSizes+1)
        yAxisLabels{j} = int2str(cacheBlockDimMin * 2^(j-1));
    end
    
    % actual plotting
    for graphCtr = 1:numGraphs
        figure('Position', [100 0 900 900]);
        
        for iterationCtr = 1:numIterations
            if (averageOrIndividualIterationGraphs == 'a')
                iterationStr = [int2str(iterationCtr), ' Iter'];
                derivedType = 1;
            elseif (averageOrIndividualIterationGraphs == 'i')
                iterationStr = ['Iter #', int2str(iterationCtr)];
                derivedType = 2;
            end

            plotArea = zeros(xCacheBlockSizes+1, yCacheBlockSizes+1);
            for i = 1:xCacheBlockSizes
                for j = 1:yCacheBlockSizes
                    plotArea(j, i) = derivedData(iterationCtr, i, j, graphVector(graphCtr), derivedType);
                end
            end

            subplot(2, 2, iterationCtr, 'align');
            pcolor(plotArea);
            caxis([0 upperLimitVector(graphCtr)]);
            axis square;
            colormap(jet);
            colorbar;

            axisLimits = caxis;
            blackFontLimits = [(axisLimits(1)+.25*(axisLimits(2)-axisLimits(1))) (axisLimits(1)+.75*(axisLimits(2)-axisLimits(1)))];
            
            for i = 1:xCacheBlockSizes
                for j = 1:yCacheBlockSizes
                    value = plotArea(j, i);
                    if ((value >= blackFontLimits(1)) && (value <= blackFontLimits(2)))
                        fontColor = 'k';
                    else
                        fontColor = 'w';
                    end
                    if (strcmpi(platform.graphStrArray(graphVector(graphCtr)), 'Time'))
                        text(i+.2, j+.5, sprintf('%-2.2f', value), 'FontSize', 12, 'Color', fontColor);
                    elseif (strcmpi(platform.graphStrArray(graphVector(graphCtr)), 'Mem. Read Traffic (Bytes/pt.)'))
                         text(i+.2, j+.5, sprintf('%-2.1f', value), 'FontSize', 12, 'Color', fontColor);
                    else
                        text(i+.2, j+.5, sprintf('%-2.2f', value), 'FontSize', 12, 'Color', fontColor);
                    end
                end
            end
            
            set(gca, 'FontSize', 10, 'XTick', get(gca, 'XTick')+0.5, 'YTick', get(gca, 'YTick')+0.5);
            set(gca, 'XTickLabel', xAxisLabels, 'FontSize', 12);
            set(gca, 'YTickLabel', yAxisLabels, 'FontSize', 12);
            xlabel('X-Dimension of Cache Block', 'FontSize', 12);
            ylabel('Y-Dimension of Cache Block', 'FontSize', 12);
            title([iterationStr, ': ', platform.procType, ' ', platform.graphStrArray{graphVector(graphCtr)}, '  [', int2str(gridDim), '^3 Grid, ', boundaryType, ' Bounds]'], 'FontSize', 12);            
        end
    end
