% This function processes the raw data from
% davinci_block_search_read_data() to produce derived data

function [derivedData] = block_search_derive_data(platformName, language, gridDim, cacheBlockDimMin, numIterations, boundaries)
    xCacheBlockSizes = log2(gridDim) - log2(cacheBlockDimMin) + 1;
    yCacheBlockSizes = log2(gridDim) - log2(cacheBlockDimMin) + 1;
    numDerivedTypes = 3;       % in order, average, individual iteration, and total
    
    numPointsInGrid = gridDim^3;
    totalPoints = numPointsInGrid;
    numFlopsPerPoint = 8;
    numFlopsInGFlop = 1e9;
    numGFlopsPerIteration = numFlopsPerPoint*numPointsInGrid/numFlopsInGFlop;

    [rawData] = block_search_raw_data(platformName, language, gridDim, cacheBlockDimMin, numIterations, boundaries);
    [platform] = platform_info(platformName, 'papi');
    
    % produce derived data
    derivedData = zeros(numIterations, xCacheBlockSizes, yCacheBlockSizes, platform.numDerivedPapiCounters+platform.numDerivedQuantities, numDerivedTypes);

    for iterationCtr = 1:numIterations
        for xCacheBlockSizeCtr = 1:xCacheBlockSizes
            for yCacheBlockSizeCtr = 1:yCacheBlockSizes
                for derivedPapiCtr = 1:(platform.numDerivedPapiCounters-1)
                    if (derivedPapiCtr == 1)
                        divideFactor = platform.clockRate;
                    else
                        divideFactor = totalPoints;
                    end

                    derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, derivedPapiCtr, 3) = min(rawData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, derivedPapiCtr, 2:size(rawData, 5)))/divideFactor;
                    derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, derivedPapiCtr, 1) = derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, derivedPapiCtr, 3)/iterationCtr;
                    if (iterationCtr == 1)
                        derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, derivedPapiCtr, 2) = derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, derivedPapiCtr, 3);
                    else
                        derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, derivedPapiCtr, 2) = derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, derivedPapiCtr, 3) - derivedData(iterationCtr-1, xCacheBlockSizeCtr, yCacheBlockSizeCtr, derivedPapiCtr, 3);
                    end
                end

                % GFlop calculation
                derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, platform.numDerivedPapiCounters+1, 1) = numGFlopsPerIteration/derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, 1, 1);
                derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, platform.numDerivedPapiCounters+1, 2) = numGFlopsPerIteration/derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, 1, 2);
                
                % Main Memory Traffic calculation
                derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, platform.numDerivedPapiCounters+2, :) = derivedData(iterationCtr, xCacheBlockSizeCtr, yCacheBlockSizeCtr, platform.largestCacheMissCounter, :) * platform.cacheLineSize;
            end
        end
    end