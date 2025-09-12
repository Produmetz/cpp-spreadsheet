#pragma once

#include "cell.h"
#include "common.h"

#include <functional>
#include <unordered_map>
#include <cstdint>

namespace std {
    template<>
    struct hash<Position> {
        size_t operator()(const Position& pos) const noexcept {
            // Упаковываем 2 числа в 32 бита (14 бит на row, 14 бит на col)
            // Оставшиеся 4 бита можно игнорировать
            const uint32_t key = 
                (static_cast<uint32_t>(pos.row) << 14) | 
                static_cast<uint32_t>(pos.col);
            
            return hash<uint32_t>{}(key);
        }
    };
}



class Sheet : public SheetInterface {
public:
    //using Table = std::unordered_map<Position, std::unique_ptr<Cell>>;

    ~Sheet();

    void SetCell(Position pos, std::string text) override;

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;

    const Cell* GetCellPtr(Position pos) const;
    Cell* GetCellPtr(Position pos);

private:
    std::unordered_map<Position, std::unique_ptr<Cell>> cells_;
};