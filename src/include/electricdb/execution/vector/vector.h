#pragma once

#include "common/types.h"
#include "nullmask.h"
#include "selection_vector.h"

namespace electricdb {
/**
 * @brief Physical type of a vector
 * 
 */
enum class VectorType : uint8_t {
	FLAT,
	CONSTANT,
	DICTIONARY
};

class Vector {
	public:
		/**
		 * @brief Construct a new Vector object
		 * 
		 * @param type 
		 * @param capacity 
		 */
		Vector(LogicalType type, uint32_t capacity);
		~Vector();

		/** @brief Disable copy constructor */
		Vector(const Vector &) = delete;

		/** @brief Disable copy assignment  */
		Vector &operator=(const Vector &) = delete;

		/** @brief Disable move constructor */
		Vector(Vector &&) noexcept;

		/** @brief Disable move assignment */
		Vector &operator=(Vector &&) noexcept;


		/**
		 * @brief Functions below are for getting metadata
		 * 
		 */
		/** @brief Return type of each element in this vector */
		LogicalType type() const noexcept;

		/** @brief Return type of this vector ie. how this vector is storing data */
		VectorType vector_type() const noexcept;

		/** @brief Returns number of elements in this vector */
		uint32_t size() const noexcept;

		/** @brief Returns maximum number of elements that can be stored in this vector */
		uint32_t capacity() const noexcept;

		/** @brief Set the number of elements in this vector */
		void set_size(uint32_t size);


		/**
		 * @brief Functions below are for data access
		 * 
		 */
		/** @brief Write access to data */
		template <typename T>
		T *data();

		/** @brief Read-only access to data */
		template <typename T>
		T *data() const;

		/** @brief Constant access support */
		template <typename T>
		T &constant_value();

		/**
		 * @brief Functions below are for null handling
		 * 
		 */

		/**
		 * @brief Check if this vector has null values
		 * 
		 * @return true if there are null values in this vector
		 * @return false if vector has no null values
		 */
		bool has_nulls() const noexcept;
		/**
		 * @brief Checks if element at specified index is null
		 * 
		 * @param idx Index to check
		 * @return true if element at idx is null
		 * @return false otherwise
		 */
		bool is_null(uint32_t idx) const noexcept;
		/**
		 * @brief Sets index in vector to null
		 * 
		 * @param idx Index to update
		 */
		void set_null(uint32_t idx);
		/**
		 * @brief Clears null if present at idx 
		 * 
		 * @param idx Index that contains element and requires null clearing
		 */
		void clear_null(uint32_t idx);

		/**
		 * @brief Checks if there is a selection vector ie. filter applied to this vector
		 * 
		 * @return true if there is a selection vector
		 * @return false otherwise
		 */
		bool has_selection() const noexcept;

		/**
		 * @brief Returns read only access to the Selection Vectors applied to this vector
		 * 
		 * @return const SelectionVector* 
		 */
		const SelectionVector *selection() const noexcept;

		/**
		 * @brief Set a selection vector for this vector
		 * 
		 * @param sel
		 */
		void set_selection(const SelectionVector *sel);

		/**
		 * @brief Remove all selection vectors from this vector
		 * 
		 */
		void clear_selection();
	private:
		LogicalType logical_type_;
		VectorType vector_type_;
		uint32_t size_;
		uint32_t capacity_;
		void *data_;
		std::unique_ptr<NullMask> nulls_;
		const SelectionVector *selection_;
		bool owns_data;
	};
} // namespace electricdb
