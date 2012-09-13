% This function reads in the block search output

function [rawData] = block_search_raw_data(platformName, language, gridDim, cacheBlockDimMin, numIterations, boundaries)
    xCacheBlockSizes = log2(gridDim) - log2(cacheBlockDimMin) + 1;
    yCacheBlockSizes = log2(gridDim) - log2(cacheBlockDimMin) + 1;
    numTrials = 5;

    if (boundaries == 'c')
        boundaryDir = 'constant';
    elseif (boundaries == 'p')
        boundaryDir = 'periodic';
    end
    
    fileName = ['../data/block_search/', boundaryDir, '/', platformName, '_ts_', int2str(gridDim), 'cubed_', language, '.out']

    [platform] = platform_info(platformName, 'papi');
    rawData = zeros(numIterations, xCacheBlockSizes, yCacheBlockSizes, platform.numPapiCounters, numTrials);

    % read in raw data
    currentLine = 14;
    for iterationCtr = 1:numIterations
        for xCacheBlockSizeCtr = 1:xCacheBlockSizes
            for yCacheBlockSizeCtr = 1:yCacheBlockSizes
                for papiCtr = 1:platform.numPapiCounters
                    rawData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, papiCtr, :) = csvread(fileName, currentLine, 0, [currentLine, 0, currentLine, numTrials-1]);
                    currentLine = currentLine + 2;
                end
                currentLine = currentLine + 13;
            end
        end
    end
