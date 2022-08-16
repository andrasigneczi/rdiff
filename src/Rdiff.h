#ifndef __RDIFF_H__
#define __RDIFF_H__

#include <memory>
#include "InputInterface.h"
#include "OutputInterface.h"
#include "HashGeneratorInterface.h"
#include "HashStorageInterface.h"
#include "ClockInterface.h"
#include "LoggerInterface.h"

#include <vector>
#include <functional>

class Rdiff final {
    friend class RdiffBuilder;
    Rdiff() noexcept = default;
    using HashValueType = int64_t;

public:
    void execute();

    struct Chunk {
        long position{};
        long hashIndex{-1};
        std::unique_ptr<std::vector<uint8_t>> block;
    };
private:
    // set functions for RdiffBuilder
    void setInput1(InputInterfaceUPtr&& input) noexcept {input1_ = std::move(input);}
    void setInput2(InputInterfaceUPtr&& input) noexcept {input2_ = std::move(input);}
    void setOutput(OutputInterfaceUPtr&& output) noexcept {output_ = std::move(output);}
    void setHashGenerator(HashGeneratorInterfaceUPtr&& h) noexcept {hashGenerator_ = std::move(h);}
    void setSignatureStorage(HashStorageInterfaceUPtr&& signatureStorage) noexcept {signatureStorage_ = std::move(signatureStorage);}
    void setClock(ClockInterfaceUPtr&& clock) noexcept {clock_ = std::move(clock);}
    void setLogger(LoggerInterfaceUPtr&& logger) noexcept {logger_ = std::move(logger);}
    void setTask(std::function<void()>&& task) noexcept {task_ = std::move(task);}

    void generateSignature();
    void generateDelta();
    void loadDelta();
    void generatePatchedOutput();
    void loadSignature();
    void generateChunksForMatchingSignatures();
    void copyContentFromNewFile(long chunkIndex, long from, long length);
    void copyChunkContentFromNewFile(size_t& chunkIndex, const Chunk& chunk, long input2Size, long& position);
    void changeHashGenerator(InputInterfaceUPtr& input);
    void saveHashFunctionType();

    void initMatchingClocks();
    void printMatchingClocksDurations();

    static constexpr long partialChunk = -1;

    InputInterfaceUPtr input1_;
    InputInterfaceUPtr input2_;
    OutputInterfaceUPtr output_;
    HashGeneratorInterfaceUPtr hashGenerator_;
    HashStorageInterfaceUPtr signatureStorage_;
    ClockInterfaceUPtr clock_; // lightweight design pattern
    ClockInterfaceUPtr clockA_; // clock for hash generator's add
    ClockInterfaceUPtr clockU_; // clock for hash generator's update
    ClockInterfaceUPtr clockFindHash_; // clock for signature search

    LoggerInterfaceUPtr logger_;
    std::function<void()> task_;

    static constexpr HashValueType blockSize_{1800};
    static constexpr HashValueType prime_{2130706381ull};
    static constexpr HashValueType multipler_{10};
    std::vector<Chunk> chunks_;
    std::vector<uint8_t> copyBuffer_;
};

using RdiffUPtr = std::unique_ptr<Rdiff>;

#endif
